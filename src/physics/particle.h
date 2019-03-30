#pragma once

#include <array>

#include "../general/drawable.h"
#include "../general/canvas.h"

#include "../color/rgb.h"

#include "../vector3d/vector3d.h"
#include "../misc/constants.h"

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
		Particle(Canvas* vue = nullptr, Vector3D x_0 = vctr::ZERO_VECTOR, Vector3D v_0 = vctr::ZERO_VECTOR, double my_mass = simcst::DEFAULT_MASS, double my_charge = simcst::DEFAULT_CHARGE, double my_radius = simcst::DEFAULT_RADIUS) :
			Drawable(vue),
			r(Vector3D(x_0)),
			v(Vector3D(v_0)),
			F(Vector3D()),
			mass(my_mass),
			charge(my_charge),
			radius(my_radius),
			color(RGB::WHITE)
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

		void setCanvas(Canvas* c);
		
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

		void move(double dt);
		virtual void evolve(double dt) override;
};

std::ostream& operator<<(std::ostream& output, Particle const& particle);
