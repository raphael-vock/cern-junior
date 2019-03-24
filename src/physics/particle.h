#pragma once

#include <array>

#include "../general/drawable.h"
#include "../general/canvas.h"

#include "../general/color.h"

#include "../vector3d/vector3d.h"
#include "physical_constants.h"

class Particle : public Drawable{
	private:
		Vector3D r; // position at time t
		Vector3D v; // velocity at time t 

		Vector3D F; // resultant force being applied 

		// Physical attributes:
		double mass;
		double charge;
		double radius;
		RGB color;

	public:
		static constexpr double DEFAULT_MASS = 1.0;
		static constexpr double DEFAULT_RADIUS = 1.0;

		static constexpr double GRAVITY_EPSILON = 1e-1;
		
		static constexpr double ETA = 0.8; // collision constant

		bool alive = true;

		Particle(Canvas* vue, double x = 0, double y = 0, double z = 0, double v_x = 0.0, double v_y = 0.0, double v_z = 0.0, double my_mass = DEFAULT_MASS, double my_charge = 0.0, double my_radius = DEFAULT_RADIUS) :
			Drawable(vue),
			r(Vector3D(x,y,z)),
			v(Vector3D(v_x,v_y,v_z)),
			F(Vector3D()),
			mass(my_mass),
			charge(my_charge),
			radius(my_radius),
			color(WHITE)
			{}

		Particle(Canvas* vue, Vector3D x_0, Vector3D v_0 = basicvector::ZERO_VECTOR, double my_mass = DEFAULT_MASS, double my_charge = 0.0, double my_radius = DEFAULT_RADIUS) :
			Drawable(vue),
			r(Vector3D(x_0)),
			v(Vector3D(v_0)),
			F(Vector3D()),
			mass(my_mass),
			charge(my_charge),
			radius(my_radius),
			color(WHITE)
			{}

		std::ostream& print(std::ostream &stream) const;
		virtual void draw(void) override{ canvas->draw(*this); }

		double getMass(void) const;
		void setMass(double my_mass);

		double getCharge(void) const;

		double getRadius(void) const;

		RGB getColor(void) const;

		Vector3D getPosition(void) const;
		Vector3D getVelocity(void) const;
		Vector3D getForce(void) const;
		
		void reset_force(void); // sets force to zero-vector
		void add_force(const Vector3D& my_F);
		void add_magnetic_force(const Vector3D& B, double dt);
		void add_electric_force(const Vector3D &E);
		void add_gravitational_force(Particle& P) const; // increments force of P by the gravitational force exerted by *this

		double gamma(void) const;
		double energy(void) const;

		void average_particle(const Particle& Q); // returns the particle whose mass is the sum of the two masses and whose position is their barycenter

		bool is_touching(const Particle& q) const;

		void swallow(Particle &q);
		void evolve(double dt);
};

std::ostream& operator<<(std::ostream& output, Particle const& particle);
