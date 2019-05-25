#pragma once

#include <array>
#include <cmath>
#include <memory>

#include "../general/drawable.h"
#include "../general/canvas.h"

#include "../color/rgb.h"

#include "../vector3d/vector3d.h"
#include "../misc/constants.h"

class Element;

class PointCharge : public Vector3D{
	protected:
		double charge;
		double gamma;
	public:
		PointCharge(const Vector3D &x_0, double q) : Vector3D(x_0), charge(q), gamma(1.0){}

		Vector3D electromagnetic_force(const PointCharge &Q) const;

		double getCharge(void) const{ return charge; }
		double getGamma(void) const{ return gamma; }

		void incorporate(const PointCharge& Q); // makes *this the "average" particle between itself and Q, weighted by charge
};

class Particle : public Drawable, public PointCharge{
	friend Beam;// TODO needed?

	protected:
		explicit Particle(Canvas* vue, const Vector3D &x_0, const Vector3D &v_0, double my_mass, double my_charge) :
			Drawable(vue),
			PointCharge(x_0,my_charge),
			v(Vector3D(v_0)),
			F(vctr::ZERO_VECTOR),
			mass(my_mass)
	{ update_attributes(); }

	private:
		Vector3D v; // velocity (in c)
		Vector3D F; // force (in N)

		double mass; // (in kg)

		double energy;

		Element* current_element;

	public:
		explicit Particle(const Vector3D &x_0, const Vector3D &v_0, double my_mass, double my_charge) :
			Drawable(nullptr),
			PointCharge(x_0,my_charge),
			v(Vector3D(v_0)),
			mass(my_mass)
		{ update_attributes(); }

		explicit Particle(const Vector3D &x_0, double E_gev, const Vector3D &dir, double mass_gev_c2, double charge_e) :
			Drawable(nullptr),
			PointCharge(x_0,phcst::E_USI*charge_e),
			v(dir.is_zero() or E_gev <= simcst::ZERO_ENERGY_GEV ? vctr::ZERO_VECTOR : sqrt(1.0 - (mass_gev_c2*mass_gev_c2)/(E_gev*E_gev))*dir.unitary()),
			mass(1e9*phcst::E_USI/phcst::C2_USI * mass_gev_c2)
		{ update_attributes(); }

		virtual std::string particle_type(void) const{ return "Generic particle"; }

		virtual std::unique_ptr<Particle> copy(void) const{ return std::unique_ptr<Particle>(new Particle(*this)); }; // polymorphic copy method

		void scale(double lambda);

		std::ostream& print(std::ostream &stream) const;
		virtual void draw(void) override{ canvas->draw(*this); }

		double getMass(void) const{ return mass; }
		virtual double getRadius(void) const{ return simcst::REPRESENTED_RADIUS_DEFAULT; };

		Vector3D getVelocity(void) const{ return v; }
		Vector3D getForce(void) const{ return F; }

		void setPosition(const Vector3D &x){ Vector3D::operator=(x); }

		void setVelocity(const Vector3D &x){ v = x; }

		void setElement(Element* e){ current_element = e; }

		virtual const RGB* getColor(void) const{ return &RGB::BLACK; }

		void setCanvas(Canvas* c){ canvas = c; }

		inline void reset_force(void){ F = vctr::ZERO_VECTOR; }

		inline void add_force(const Vector3D& my_F){ F += my_F; };
		void add_magnetic_force(const Vector3D& B, double dt);
		void add_electric_force(const Vector3D &E);
		void receive_electromagnetic_force(const PointCharge &Q);

		double getEnergy(void) const{ return energy; };

		inline void update_attributes(void){
			gamma = 1.0/(sqrt(1.0 - v.norm2()));
			energy = gamma*mass*phcst::C2_USI; 
		}

		void move(double dt);

		void insert_into_tree(void);
		void evolve(double dt);

		bool has_collided(void) const;

		Vector3D radial_vector_calculation(void) const; // returns the vector used to calculate radial position and velocity 
		double radial_position(void) const;
		double vertical_position(void) const;
		double radial_velocity(void) const;
		double vertical_velocity(void) const;
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
