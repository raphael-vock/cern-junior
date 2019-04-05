#pragma once

#include <array>

#include "../general/drawable.h"
#include "../general/canvas.h"

#include "../color/rgb.h"

#include "../vector3d/vector3d.h"
#include "../misc/constants.h"

class Particle : public Drawable{
	private:
		// TODO come up with a good system of units!
		
		Vector3D r;
		Vector3D v;
		Vector3D F;

		// TODO make const when possible
		double mass;
		double charge;

		double radius;
		RGB color;

	public:
		explicit Particle(Canvas* vue, const Vector3D &x_0, const Vector3D &v_0, double my_mass, double my_charge, double my_radius, const RGB &my_color = RGB::BLUE) :
			Drawable(vue),
			r(Vector3D(x_0)),
			v(Vector3D(v_0)),
			F(vctr::ZERO_VECTOR),
			mass(my_mass),
			charge(my_charge),
			radius(my_radius),
			color(my_color)
			{}

		std::ostream& print(std::ostream &stream) const;
		virtual void draw(void) override{ canvas->draw(*this); }

		double getMass(void) const{ return mass; }
		double getCharge(void) const{ return charge; }
		double getRadius(void) const{ return radius; }
		RGB getColor(void) const{ return color; }
		Vector3D getPosition(void) const{ return r; }
		Vector3D getVelocity(void) const{ return v; }
		Vector3D getForce(void) const{ return F; }

		void reset_force(void){ F = vctr::ZERO_VECTOR; }

		void add_force(const Vector3D& my_F);
		void add_magnetic_force(const Vector3D& B, double dt);
		void add_electric_force(const Vector3D &E);
		void apply_gravitational_force(Particle& P) const; // applies gravitational force on P

		double gamma(void) const;
		double energy(void) const; // in GeV

		void average_particle(const Particle& Q); // returns the particle whose mass is the sum of the two masses and whose position is their barycenter

		bool is_touching(const Particle& q) const;

		void swallow(Particle &q);

		void move(double dt);
		virtual void evolve(double dt) override;
};

std::ostream& operator<<(std::ostream& output, Particle const& particle);
