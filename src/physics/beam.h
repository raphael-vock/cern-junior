#include <vector>
#include <memory>
#include <random>

#include "../misc/exceptions.h"

#include "../physics/accelerator.h"

class Beam : public Drawable, protected std::vector<Particle*>{
	protected:
		std::unique_ptr<Particle> model_particle;
		const uint N; // number of particles that will effectively be created
		const double lambda; // scaling factor between reference_particles and the macro-particles

		Accelerator* habitat; // the accelerator that the beam lives in
	public:
		explicit Beam(Accelerator& machine, const Particle &p, uint number_of_particles, double my_lambda);

		virtual ~Beam(void) override{}

		void update(void);

		void draw_particles(void) const{ for(const auto &p : *this) p->draw(); }
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

		virtual std::ostream& print(std::ostream& output) const;
};

class CircularBeam : public Beam{
	// generates a circular beam according to some distribution
	private:
		std::random_device gen; // seed generator
		RandomVector3D position_offset; // random 3D-offset around ideal positions
		RandomVector3D velocity_offset; // random 3D-offset around ideal velocities
	public:
		explicit CircularBeam(Accelerator& machine, const Particle &p, uint number_of_particles, double my_lambda, const RandomVector3D &my_distr_x, const RandomVector3D &my_distr_v) :
			Beam(machine, p, number_of_particles, my_lambda),
			position_offset(my_distr_x),
			velocity_offset(my_distr_v)
		{}
		virtual void activate(void) override;
};

class GaussianCircularBeam : public CircularBeam{
	// A circular beam with a random Gaussian offset in three dimensions
	private:
		double sigma_x; // standard deviation on position
		double sigma_v; // standard deviation on velocity

	public:
		explicit GaussianCircularBeam(Accelerator& machine, const Particle &p, uint number_of_particles, double my_lambda, double my_sigma_x, double my_sigma_v) :
			CircularBeam(machine, p, number_of_particles, my_lambda, GaussianVector3D(my_sigma_x), GaussianVector3D(my_sigma_v)),
			sigma_x(my_sigma_x),
			sigma_v(my_sigma_v)
		{}

		virtual std::ostream& print(std::ostream& output) const override;
};

class UniformCircularBeam : public CircularBeam{
	// A circular beam with a random uniform offset in three dimensions
	private:
		double delta_x; // variance in position
		double delta_v; // variance in velocity

	public:
		explicit UniformCircularBeam(Accelerator& machine, const Particle &p, uint number_of_particles, double my_lambda, double my_delta_x, double my_delta_v) :
			CircularBeam(machine, p, number_of_particles, my_lambda, UniformVector3D(my_delta_x), UniformVector3D(my_delta_v)),
			delta_x(my_delta_x),
			delta_v(my_delta_v)
		{}

		virtual std::ostream& print(std::ostream& output) const override;
};
