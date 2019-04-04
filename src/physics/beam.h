#include "../vector3d/vector3d.h"
#include "particle.h"
#include <vector>
#include <array>

class Beam {
	private :
	const Particle reference_particle;
	uint particle_number;
	uint macro_particle_factor;
	std::vector<Particle*> particle_list;

	public :
	Beam(const Particle& p, uint my_particle_number, uint my_macro_particle_factor) :
	reference_particle(p),
	particle_number(my_particle_number),
	macro_particle_factor(my_macro_particle_factor)
	{}

	Beam(Canvas* vue, const Vector3D &x_0, const Vector3D &v_0, double my_mass, double my_charge, double my_radius, uint my_particle_number, uint my_macro_particle_factor, const RGB &my_color = RGB::BLUE) :
	reference_particle(vue, x_0, v_0, my_mass, my_charge, my_radius, my_color),
	particle_number(my_particle_number),
	macro_particle_factor(my_macro_particle_factor)
	{}

	~Beam() {for (uint i(0); i < particle_number; ++i) {delete particle_list[i];}}

	void initialise(void); // allocates dynamically particle_number particles whose pointers are saved in particle_list

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
