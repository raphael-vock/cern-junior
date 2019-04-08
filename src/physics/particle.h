#pragma once

#include <array>
#include <cmath>

#include "../general/drawable.h"
#include "../general/canvas.h"

#include "../color/rgb.h"

#include "../vector3d/vector3d.h"
#include "../misc/constants.h"

class Particle : public Drawable{
	protected:
		explicit Particle(Canvas* vue, const Vector3D &x_0, const Vector3D &v_0, double my_mass, double my_charge, double my_radius, RGB const* my_color = &RGB::WHITE) :
			Drawable(vue),
			r(Vector3D(x_0)),
			v(Vector3D(v_0)),
			F(vctr::ZERO_VECTOR),
			mass(my_mass),
			charge(my_charge),
			radius(my_radius),
			color(my_color)
	{}
	private:
		Vector3D r; // position (in m)
		Vector3D v; // velocity (in c)
		Vector3D F; // force (in N)

		double mass; // (in kg)
		double charge; // (in C)

		// for graphical representation (i.e. not physical):
		double radius;
		RGB const* color;

	public:
		explicit Particle(const Vector3D &x_0, const Vector3D &v_0, double my_mass, double my_charge, double my_radius = 0.0, RGB const* my_color = &RGB::WHITE) :
			Drawable(nullptr),
			r(Vector3D(x_0)),
			v(Vector3D(v_0)),
			F(0,0,0),
			mass(my_mass),
			charge(my_charge),
			radius(my_radius),
			color(my_color)
		{}

		explicit Particle(const Vector3D &x_0_m, double E_gev, const Vector3D &dir, double mass_gev_c2, double charge_e, double my_radius = simcst::REPRESENTED_RADIUS_ELECTRON, RGB const* my_color = &RGB::WHITE) :
			Drawable(nullptr),
			r(x_0_m),
			v(dir.is_zero() or E_gev <= simcst::ZERO_ENERGY_GEV ? vctr::ZERO_VECTOR : sqrt(1.0 - (mass_gev_c2*mass_gev_c2)/(E_gev*E_gev))*dir.unitary()),
			F(0,0,0),
			mass(1e9*phcst::E_USI/phcst::C2_USI * mass_gev_c2),
			charge(phcst::E_USI * charge_e),
			radius(my_radius),
			color(my_color)
		{}

		virtual Particle* copy(void) const{ return new Particle(*this); }; // polymorphic copy method

		void scale(double lambda);

		std::ostream& print(std::ostream &stream) const;
		virtual void draw(void) override{ canvas->draw(*this); }

		double getMass(void) const{ return mass; }
		double getCharge(void) const{ return charge; }
		double getRadius(void) const{ return radius; }
		RGB getColor(void) const{ return *color; }
		Vector3D getPosition(void) const{ return r; }
		Vector3D getVelocity(void) const{ return v; }
		Vector3D getForce(void) const{ return F; }

		void setCanvas(Canvas* c){ canvas = c; }
		void setPosition(const Vector3D &x){ r = x; }
		void setVelocity(const Vector3D &u){ v = u; }

		void reset_force(void){ F = vctr::ZERO_VECTOR; }

		void add_force(const Vector3D& my_F);
		void add_magnetic_force(const Vector3D& B, double dt);
		void add_electric_force(const Vector3D &E);
		void apply_gravitational_force(Particle& P) const; // applies gravitational force on P

		double gamma(void) const;
		double energy(void) const; // in GeV

		void average_particle(const Particle& Q); // returns the particle whose mass is the sum of the two masses and whose position is their barycenter

		bool is_touching(const Particle& q) const;

		void move(double dt);
		virtual void evolve(double dt) override;
};

class Electron : public Particle{
	public:
		explicit Electron(const Vector3D &x_0, const double E, const Vector3D &dir) :
			Particle(x_0, E, dir, phcst::MASS_ELECTRON_GEV_C2, -1.0, simcst::REPRESENTED_RADIUS_ELECTRON, &RGB::BLUE)
		{}

		virtual Electron* copy(void) const override{ return new Electron(*this); }
};

class Proton : public Particle{
	public:
		explicit Proton(const Vector3D &x_0, const double E, const Vector3D &dir) :
			Particle(x_0, E, dir, phcst::MASS_PROTON_GEV_C2, 1.0, simcst::REPRESENTED_RADIUS_PROTON, &RGB::BLUE)
		{}

		virtual Proton* copy(void) const override{ return new Proton(*this); }
};

std::ostream& operator<<(std::ostream& output, Particle const& particle);
