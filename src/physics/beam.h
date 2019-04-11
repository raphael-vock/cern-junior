#include <vector>
#include <memory>

#include "../misc/exceptions.h"

#include "../accelerator/accelerator.h"

class Beam : public Drawable, protected std::vector<std::unique_ptr<std::unique_ptr<Particle>>>{
	protected:
		const Particle &model_particle;
		const uint N; // number of particles that will effectively be created
		const double lambda; // scaling factor between reference_particles and the macro-particles

		Accelerator* habitat; // the accelerator that the beam lives in
	public:
		explicit Beam(Accelerator& machine, const Particle &p, uint number_of_particles, double my_lambda) :
			Drawable(machine.getCanvas()),
			model_particle(*p.copy()),
			N(number_of_particles / my_lambda),
			lambda(my_lambda),
			habitat(&machine)
		{ 
			if(my_lambda <= simcst::ZERO_LAMBDA) throw excptn::ZERO_LAMBDA; 
		}


		virtual ~Beam(void) override{}

		void draw_particles(void) const{ for(const auto &p : *this) (**p).draw(); }
		virtual void draw(void) override{ canvas->draw(*this); }

		virtual void activate(void) = 0;

		Vector3D mean_position(void) const;
		Vector3D mean_velocity(void) const;

		double vertical_emittance(void) const;
		double radial_emittance(void) const;

		std::array<double,3> radial_ellipse_coefficients(void) const; // A11, A12, A22 in this order 
		std::array<double,3> vertical_ellipse_coefficients(void) const; // A11, A12, A22 in this order 

		double mean_energy(void) const;

		void evolve(double dt);

		std::ostream& print(std::ostream& output) const;
}; 

class CircularBeam : public Beam{
	public:
		using Beam::Beam;
		virtual void activate(void) override;
}; 
