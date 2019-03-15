#ifndef PARTICLE_H
#define PARTICLE_H

#include <array>

#include "../general/color.h"
#include "../vector3d/vector3d.h"
#include "physical_constants.h"

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

		static constexpr double GRAVITY_EPSILON = 1e-3;
		
		static constexpr double ETA = 0.8; // collision constant

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
			color(WHITE)
			{}

		Particle(Vector3D x_0, Vector3D v_0 = Vector3D::ZERO_VECTOR, double my_mass = DEFAULT_MASS, double my_charge = 0.0, double my_radius = DEFAULT_RADIUS) :
			r(Vector3D(x_0)),
			r_p(Vector3D(x_0)),
			v(Vector3D(v_0)),
			v_p(Vector3D(v_0)),
			F(Vector3D()),
			mass(my_mass),
			charge(my_charge),
			radius(my_radius),
			color(WHITE)
			{}

		double getMass(void) const;
		void setMass(double my_mass);

		double getCharge(void) const;

		double getRadius(void) const;

		RGB getColor(void) const;

		const Vector3D* getPosition(void) const;
		const Vector3D* getVelocity(void) const;
		Vector3D getMomentum(void) const;
		const Vector3D* getForce(void) const;
		
		void reset_force(void); // sets force to zero-vector
		void add_force(const Vector3D & my_F);
		void add_magnetic_force(const Vector3D& B, double dt);
		void add_gravitational_force(Particle& P) const; // increments force of P by the gravitational force exerted by *this

		double gamma(void) const;
		double energy(void) const;

		void average_particle(const Particle& Q); // returns the particle whose mass is the sum of the two masses and whose position is their barycenter

		bool is_touching(const Particle& q) const;

		void swallow(Particle &q);
		void evolve(double dt);
};

std::ostream& operator<<(std::ostream& output, Particle const& particle);

#endif
