#include <vector>
#include <memory>

#include "../accelerator/accelerator.h"

class Beam : public Drawable, protected std::vector<std::unique_ptr<Particle>>{
	protected:
		const Particle reference_particle;
		const uint N; // initial number of particles
		const double lambda; // scaling factor between reference_particles and the macro-particles

		std::shared_ptr<Accelerator> habitat;
	public:
		Beam(const Accelerator &machine, const Particle &p, uint my_N, double my_lambda) :
			Drawable(machine.getCanvas()),
			reference_particle(p),
			N(my_N),
			lambda(my_lambda)
		{}

		virtual ~Beam(void) override{}

		virtual void initialize(void) = 0;

		Vector3D mean_position(void) const;
		Vector3D mean_velocity(void) const;

		double vertical_emittance(void) const;
		double radial_emittance(void) const;

		std::array<double,3> radial_ellipse_coefficients(void) const; // A11, A12, A22 in this order 
		std::array<double,3> vertical_ellipse_coefficients(void) const; // A11, A12, A22 in this order 

		double mean_energy(void) const;

		void evolve(double dt) override;
}; 

class Circular_beam : public Beam{
	public:
		virtual void initialize(void) override;
}; 
