#ifndef PARTICLE_H
#define PARTICLE_H

#include "vector3d.h"
#include <vector>
#include <array>
#include <math.h>

typedef std::array<double,3> RGB;

class Particle{
	private:
		Vector3D r;// position at time t
		Vector3D r_p;// position at time t-dt

		Vector3D v;// velocity at time t 
		Vector3D v_p;// velocity at time t-dt

		Vector3D F;// resultant force being applied 

		// physical attributes
		double mass;
		double charge;
		double radius;
		RGB color;

	public:
		static constexpr double DEFAULT_MASS = 1.0;
		static constexpr double DEFAULT_RADIUS = 1.0;

		static constexpr double G = 1e-3;
		static constexpr double EPSILON_SQUARED = 1e-2; // softening constant

		static constexpr double C = 3e8;
		static constexpr double GeV = 6.24e9;
		bool alive = true;

		Particle(double x = 0, double y = 0, double z = 0, double v_x = 0.0, double v_y = 0.0, double v_z = 0.0, double my_mass = DEFAULT_MASS, double my_charge = 0.0, double my_radius = DEFAULT_RADIUS) :
			r(Vector3D(x,y,z)),
			r_p(Vector3D(x,y,z)),
			v(Vector3D(v_x,v_y,v_z)),
			v_p(Vector3D(v_x,v_y,v_z)),
			F(Vector3D()),
			mass(my_mass),
			charge(my_charge),
			radius(my_radius),
			color({1.0,1.0,0.0})
			{}

		Particle(Vector3D x_0, Vector3D v_0 = ZERO_VECTOR, double my_mass = DEFAULT_MASS, double my_charge = 0.0, double my_radius = DEFAULT_RADIUS) :
			r(Vector3D(x_0)),
			r_p(Vector3D(x_0)),
			v(Vector3D(v_0)),
			v_p(Vector3D(v_0)),
			F(Vector3D()),
			mass(my_mass),
			charge(my_charge),
			radius(my_radius),
			color({1.0,1.0,1.0})
			{}

		double getMass(void) const;
		void setMass(double my_mass);

		double getRadius(void) const;

		RGB getColor(void) const;

		const Vector3D* getPosition(void) const;
		const Vector3D* getVelocity(void) const;
		Vector3D getMomentum(void) const;
		const Vector3D* getForce(void) const;

		void barycenter(const Particle& P); // turns P into a particle whose mass is the sum of both particle's masses
								
		void increment_gravity(Particle& P) const; // increments force of P by the gravitational force exerted by *this

		void resetForce(void); // sets force to zero-vector

		bool is_touching(const Particle& q) const;

		void evolve(double dt);
		void swallow(Particle q);
};

const Vector3D center_of_mass(std::vector<Particle> list);

#endif
