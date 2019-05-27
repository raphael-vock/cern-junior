#include <vector>
#include <memory>

#include "../misc/exceptions.h"

#include "../accelerator/accelerator.h"

class Beam : public Drawable, protected std::vector<std::unique_ptr<std::unique_ptr<Particle>>>{
	protected:
		std::unique_ptr<Particle> model_particle;
		const uint N; // number of particles that will effectively be created
		const double lambda; // scaling factor between reference_particles and the macro-particles

		Accelerator* habitat; // the accelerator that the beam lives in
	public:
		explicit Beam(Accelerator& machine, const Particle &p, uint number_of_particles, double my_lambda);

		virtual ~Beam(void) override{}

		void update(void);

		void draw_particles(void) const{ for(const auto &p : *this) (**p).draw(); }
		virtual void draw(void) override{ canvas->draw(*this); }

		virtual void activate(void) = 0;

		double mean_radial_position_squared(void) const;
		double mean_vertical_position_squared(void) const;

		double mean_radial_velocity_squared(void) const;
		double mean_vertical_velocity_squared(void) const;

		double mean_radial_product(void) const;
		double mean_vertical_product(void) const;

		// note that the above functions are not used to compute emittance for complexity matters
		double vertical_emittance(void) const;
		double radial_emittance(void) const;

		std::array<double,3> radial_ellipse_coefficients(void) const; // A11, A12, A22 in this order
		std::array<double,3> vertical_ellipse_coefficients(void) const; // A11, A12, A22 in this order

		double mean_energy(void) const;

		std::ostream& print(std::ostream& output) const;
};

class CircularBeam : public Beam{
	public:
		using Beam::Beam;
		virtual void activate(void) override;
};
