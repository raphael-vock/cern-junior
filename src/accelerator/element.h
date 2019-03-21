#pragma once

#include <functional> // for std::function
#include <memory>
#include <vector>
#include <cmath> // for isinf

#include "../vector3d/vector3d.h"
#include "../physics/particle.h"

typedef std::function<double(Vector3D)> ScalarField;
typedef std::function<Vector3D(Vector3D)> VectorField; 

class Element{
	protected:
		Vector3D entry_point; // entry position
		Vector3D exit_point; // exit position

		double radius; // radius of the vaccum chamber
		double curvature; // radial curvature (potentially infinite)

		std::shared_ptr<Element> successor; // points to the following element

		std::vector<std::unique_ptr<Particle>> particle_list; // list of particles contained inside

	public:
		static constexpr double INFINITE_RADIUS = std::numeric_limits<double>::infinity();

		Element(const Vector3D& entry, const Vector3D& exit, double my_radius, double my_curvature, std::shared_ptr<Element> my_successor) :
			entry_point(entry),
			exit_point(exit),
			radius(my_radius),
			curvature(my_curvature),
			successor(my_successor)
		{}

		Vector3D center(void) const; // returns the center of circular element assuming curvature is finite

		bool has_collided(const Particle& p) const; // returns true iff p has collided with the element's edge
		bool has_left(const Particle& p) const; // returns true iff p has passed to the next element
		
		virtual Vector3D lorentz_force(const Particle& p) const = 0;
		void add_lorentz_force(Particle &p) const;
}; 

class Electric_element : public Element{
	private:
		VectorField E; // electric field
	public:
		Electric_element(const Vector3D& entry, const Vector3D& exit, double my_radius, double my_curvature, std::shared_ptr<Element> my_successor, VectorField electric_field) :
			Element(entry,exit,my_radius,my_curvature,my_successor),
			E(electric_field)
		{}
		virtual Vector3D lorentz_force(const Particle& p) const override;
};

class Magnetic_element : public Element{
	private:
		VectorField B; // magnetic field
	public:
		Magnetic_element(const Vector3D& entry, const Vector3D& exit, double my_radius, double my_curvature, std::shared_ptr<Element> my_successor, VectorField magnetic_field) :
			Element(entry,exit,my_radius,my_curvature,my_successor),
			B(magnetic_field)
		{}
		virtual Vector3D lorentz_force(const Particle& p) const override;
};

class Dipole : public Magnetic_element{
	public:
		Dipole(const Vector3D& entry, const Vector3D& exit, double my_radius, double my_curvature, std::shared_ptr<Element> my_successor, double magnetic_amplitude) : Magnetic_element(entry,exit,my_radius,my_curvature,my_successor,[=](Vector3D v){ return magnetic_amplitude*basicvector::Z_VECTOR;}){ if(isinf(curvature)) throw 5; }
};
