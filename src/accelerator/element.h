#pragma once

#include <vector>
#include <cmath>
#include <functional>
#include <memory> // for unique_ptr

#include "../general/drawable.h"
#include "../misc/exceptions.h"

#include "../physics/particle.h"
#include "../physics/node.h"

class Element : public Drawable, public Node{
	protected:
		Vector3D entry_point; // entry position
		Vector3D exit_point; // exit position

		const double radius; // radius of the vaccum chamber
		const double curvature; // radial curvature (potentially zero)

		Element* successor = nullptr; // pointer to the following element
		Element* predecessor = nullptr; // pointer to the previous element

		const std::shared_ptr<double> clock;

		Vector3D dir;
		double length;

		// Orthonormal basis of the plane containing the element. Useful for graphics
		Vector3D u;
		Vector3D v;
		Vector3D w;

	public:
		virtual ~Element(void){}

		Element(Canvas* display, const Vector3D& entry, const Vector3D& exit, double my_radius, double my_curvature, std::shared_ptr<double> my_clock);

		void setCanvas(Canvas* c){ canvas = c; }

		Vector3D getEntry_point(void) const{ return entry_point; }
		Vector3D getExit_point(void) const{ return exit_point; }
		double getRadius(void) const{ return radius; }
		double getCurvature(void) const{ return curvature; }

		virtual const RGB* getColor(void) const = 0;

		Vector3D getBasis_vector_u(void) const{ return u; }
		Vector3D getBasis_vector_v(void) const{ return v; }
		Vector3D getBasis_vector_w(void) const{ return w; }
		Vector3D getDir(void) const{ return dir; }

		double getLength(void) const{ return length; };

		Element* getSuccessor(void) const{ return successor; }
		Element* getPredecessor(void) const{ return predecessor; }

		void setSuccessor(Element* my_successor){ successor = my_successor; }
		void setPredecessor(Element* my_predecessor){ predecessor = my_predecessor; }

		void apply_forces(Particle &p, double dt) const;

		virtual std::ostream& print(std::ostream& output) const;
		// Base method prints only basic information (i.e. about its shape)
		// Subclass overrides will add additional information e.g. type of the element, electric/magnetic fields, other parameters...

		void link(Element &nextElement);

		bool is_straight(void) const;
		Vector3D center(void) const; // returns the center of circular element assuming curvature is non-zero

		Vector3D direction(void) const; // returns the vector exit_point - entry_point
		Vector3D unit_direction(void) const; // returns director().unitary()

		Vector3D relative_coords(const Vector3D &x) const;
		Vector3D local_coords(const Vector3D &x) const;

		Vector3D inverse_curvilinear_coord(double s) const; // returns point on the trajectory with given curvilinear coordinate
		Vector3D local_trajectory(double s) const; // returns unit vector in the direciton of the local trajectory of the point with curvilinear coordinate s

		double curvilinear_coord(const Vector3D &x) const;

		double orthogonal_offset(const Vector3D &r) const;
		bool has_collided(const Vector3D &r) const; // returns true iff r has collided with the element's edge
		bool is_after(const Vector3D &r) const; // returns true iff r has passed to the next element
		bool is_before(const Vector3D &r) const; // returns true iff r has passed to the next element

		bool contains(const Vector3D &r) const{ return not is_after(r) and not is_before(r) and not has_collided(r); }// returns true iff r has passed to the next element;

		void sort(void);

		virtual void apply_lorentz_force(Particle &, double) const = 0;
		void evolve(double dt);
};

std::ostream& operator<<(std::ostream& output, const Element &E);

class StraightSection : public Element{
	public:
		StraightSection(Canvas* display, const Vector3D& entry, const Vector3D& exit, double my_radius, std::shared_ptr<double> my_clock) :
			Element(display, entry, exit, my_radius,0.0,my_clock)
		{}
		virtual ~StraightSection(void) override{}

		virtual std::ostream& print(std::ostream& output) const override;
		virtual void draw(void) override{ canvas->draw(*this); }

		virtual const RGB* getColor(void) const override{ return &RGB::SKY_BLUE; }

		virtual void apply_lorentz_force(Particle& p, double dt) const override{ return; } // no electromagnetic interaction
};

class ElectricElement : public Element{
	public:
		using Element::Element;
		virtual ~ElectricElement(void) override{}

		virtual const RGB* getColor(void) const override{ return &RGB::BLUE; }
		virtual void apply_lorentz_force(Particle& p, double dt) const override;
		virtual Vector3D E(const Vector3D &x, double t) const = 0;
};

class MagneticElement : public Element{
	public:
		using Element::Element;
		virtual ~MagneticElement(void) override{}

		virtual const RGB* getColor(void) const override{ return &RGB::RED; }

		virtual void apply_lorentz_force(Particle& p, double dt) const override;
		virtual Vector3D B(const Vector3D &x, double t) const = 0;
};

class Dipole : public MagneticElement{
	private:
		const double B_0; // constant amplitude of the magnetic field generated by the dipole
	public:
		Dipole(Canvas* display, const Vector3D& entry, const Vector3D& exit, double my_radius, double my_curvature, std::shared_ptr<double> my_clock, double my_B_0) :
			MagneticElement(display, entry, exit, my_radius, my_curvature, my_clock), B_0(my_B_0)
		{}

		virtual std::ostream& print(std::ostream& output) const override;

		virtual void draw(void) override{ canvas->draw(*this); }

		virtual Vector3D B(const Vector3D &x, double dt) const override final;
};

class Quadrupole : public MagneticElement{
	private:
		const double b; // parameter of the quadrupole
	public:
		Quadrupole(Canvas* display, const Vector3D& entry, const Vector3D& exit, double my_radius, std::shared_ptr<double> my_clock, double my_b) :
			MagneticElement(display, entry, exit, my_radius, 0.0, my_clock), b(my_b)
		{}

		virtual Vector3D B(const Vector3D &x, double dt) const override final;

		virtual std::ostream& print(std::ostream& output) const override;

		virtual void draw(void) override{ canvas->draw(*this); }
};

class RadiofrequencyCavity : public ElectricElement{
	private:
		const double E_0;
		const double omega;
		const double kappa;
		const double phi;
	public:
		RadiofrequencyCavity(Canvas* display, const Vector3D& entry, const Vector3D& exit, double my_radius, std::shared_ptr<double> my_clock, double my_E_0, double my_omega, double my_kappa, double my_phi) :
			ElectricElement(display, entry, exit, my_radius, 0.0, my_clock),
			E_0(my_E_0),
			omega(my_omega),
			kappa(my_kappa),
			phi(my_phi)
		{}

		virtual Vector3D E(const Vector3D &x, double dt) const override final;

		virtual std::ostream& print(std::ostream& output) const override;

		virtual void draw(void) override{ canvas->draw(*this); }
};
