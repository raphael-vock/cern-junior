#pragma once

#include <array>
#include <cmath>
#include <memory>

#include "../general/drawable.h"
#include "../general/canvas.h"

#include "../color/rgb.h"

#include "../vector3d/vector3d.h"
#include "../misc/constants.h"

class Particle : public Drawable{
	protected:
		explicit Particle(Canvas* vue, const Vector3D &x_0, const Vector3D &v_0, double my_mass, double my_charge, RGB const* my_color = &RGB::WHITE) :
			Drawable(vue),
			r(Vector3D(x_0)),
			v(Vector3D(v_0)),
			F(vctr::ZERO_VECTOR),
			mass(my_mass),
			charge(my_charge)
	{ update_gamma(); }
	private:
		Vector3D r; // position (in m)
		Vector3D v; // velocity (in c)
		Vector3D F; // force (in N)

		double mass; // (in kg)
		double charge; // (in C)

		// derived physical attributes:
		double gamma;

	public:
		explicit Particle(const Vector3D &x_0, const Vector3D &v_0, double my_mass, double my_charge) :
			Drawable(nullptr),
			r(Vector3D(x_0)),
			v(Vector3D(v_0)),
			F(0,0,0),
			mass(my_mass),
			charge(my_charge)
		{ update_gamma(); }

		explicit Particle(const Vector3D &x_0_m, double E_gev, const Vector3D &dir, double mass_gev_c2, double charge_e) :
			Drawable(nullptr),
			r(x_0_m),
			v(dir.is_zero() or E_gev <= simcst::ZERO_ENERGY_GEV ? vctr::ZERO_VECTOR : sqrt(1.0 - (mass_gev_c2*mass_gev_c2)/(E_gev*E_gev))*dir.unitary()),
			F(0,0,0),
			mass(1e9*phcst::E_USI/phcst::C2_USI * mass_gev_c2),
			charge(phcst::E_USI * charge_e)
		{ update_gamma(); }

		virtual std::string particle_type(void) const{ return "Generic particle"; }

		virtual std::unique_ptr<Particle> copy(void) const{ return std::unique_ptr<Particle>(new Particle(*this)); }; // polymorphic copy method

		void scale(double lambda);

		std::ostream& print(std::ostream &stream) const;
		virtual void draw(void) override{ canvas->draw(*this); }

		double getMass(void) const{ return mass; }
		double getCharge(void) const{ return charge; }
		virtual double getRadius(void) const{ return 0.0; };

		Vector3D getPosition(void) const{ return r; }
		Vector3D getVelocity(void) const{ return v; }
		Vector3D getForce(void) const{ return F; }

		virtual const RGB* getColor(void) const{ return &RGB::BLACK; }

		void setCanvas(Canvas* c){ canvas = c; }
		void setPosition(const Vector3D &x){ r = x; }
		void setVelocity(const Vector3D &u){ v = u; }

		void reset_force(void){ F = vctr::ZERO_VECTOR; }

		void add_force(const Vector3D& my_F);
		void add_magnetic_force(const Vector3D& B, double dt);
		void add_electric_force(const Vector3D &E);
		void apply_electromagnetic_force(Particle& P) const; // applies gravitational force on P

		void update_gamma(void);
		double energy(void) const; // in GeV

		void incorporate(const Particle& Q); // makes *this the "average" particle between itself and Q, weighted by charge

		bool is_touching(const Particle& q) const;

		void move(double dt);
		void evolve(double dt);
};

class Electron : public Particle{
	public:
		explicit Electron(const Vector3D &x_0, const double E, const Vector3D &dir) :
			Particle(x_0, E, dir, phcst::MASS_ELECTRON_GEV_C2, -1.0)
		{}

		virtual double getRadius(void) const override{ return simcst::REPRESENTED_RADIUS_ELECTRON; };

		virtual std::string particle_type(void) const override{ return "Electron"; }

		virtual const RGB* getColor(void) const override{ return &RGB::GREEN; }

		virtual std::unique_ptr<Particle> copy(void) const override{ return std::unique_ptr<Electron>(new Electron(*this)); }; // polymorphic copy method
};

class Proton : public Particle{
	public:
		explicit Proton(const Vector3D &x_0, const double E, const Vector3D &dir) :
			Particle(x_0, E, dir, phcst::MASS_PROTON_GEV_C2, 1.0)
		{}

		virtual double getRadius(void) const override{ return simcst::REPRESENTED_RADIUS_PROTON; };

		virtual std::string particle_type(void) const override{ return "Proton"; }

		virtual const RGB* getColor(void) const override{ return &RGB::BLUE; }

		virtual std::unique_ptr<Particle> copy(void) const override{ return std::unique_ptr<Proton>(new Proton(*this)); }; // polymorphic copy method
};

std::ostream& operator<<(std::ostream& output, Particle const& particle);
