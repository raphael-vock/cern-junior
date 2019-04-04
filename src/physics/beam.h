#include <vector>
#include <array>
#include <memory>

#include "../vector3d/vector3d.h"
#include "particle.h"

class Beam {
	protected :
	const Particle reference_particle;
	size_t particle_number;
	const size_t macro_particle_factor;
	std::vector<std::unique_ptr<Particle>> particle_list;

	public :
	Beam(const Particle& p, size_t my_particle_number, size_t my_macro_particle_factor) :
	reference_particle(p),
	particle_number(my_particle_number),
	macro_particle_factor(my_macro_particle_factor)
	{}

	Beam(Canvas* vue, const Vector3D &x_0, const Vector3D &v_0, double my_mass, double my_charge, double my_radius, size_t my_particle_number, size_t my_macro_particle_factor, const RGB &my_color = RGB::BLUE) :
	reference_particle(vue, x_0, v_0, my_mass, my_charge, my_radius, my_color),
	particle_number(my_particle_number),
	macro_particle_factor(my_macro_particle_factor)
	{}

	~Beam() {}

	virtual void initialise(void) = 0; // allocates dynamically Particle unique pointers saved in particle_list
	void setParticle_number(size_t number) {particle_number = number;}
	void decrementParticle_number(void) {if (not (particle_number == 0)) --particle_number;}

	Vector3D radial_average_position(void) const; // returns average position of the macro particles along radial axis
	Vector3D vertical_average_position(void) const; // returns average position of the macro particles along vertical axis

	Vector3D radial_average_velocity(void) const;
	Vector3D vertical_average_velocity(void) const;

	double vertical_emittance(void) const; // returns the emittance of a beam
	double radial_emittance(void) const; // returns the emittance of a beam

	std::array<double,3> radial_ellipse_coefficients(void) const; // A11, A12, A22 in this order 
	std::array<double,3> vertical_ellipse_coefficients(void) const; // A11, A12, A22 in this order 

	double average_energy(void) const;

	void move(double dt);
	void evolve(double dt);
}; 

class CircularBeam : public Beam {
	public :
	virtual void initialise(void) override;
}; 
