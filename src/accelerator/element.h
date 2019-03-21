#pragma once

#include "../vector3d/vector3d.h"
#include "../physics/particle.h"
#include <memory>
#include <vector>

class Element{
	protected :
		enum element_type { MAGNETIC, ELECTRIC };
		element_type type;
		Vector3D entry_point; // entry position
		Vector3D exit_point; // exit position
		double radius; // radius of the vaccum chamber

		std::shared_ptr<Element> next_element; // points to the following element
		std::vector<std::unique_ptr<Particle>> particle_list; // ensures that a particle is contained in a single element

	public :
		Element(const Vector3D& entry, const Vector3D& exit, double n_radius, element_type n_type, std::shared_ptr<Element> n_element = nullptr) :
			entry_point(entry),
			exit_point(exit),
			radius(n_radius),
			next_element(n_element)
		{}

		Vector3D getEntry_point(void) const;
		Vector3D getExit_point(void) const;
		double getRadius(void) const;

		virtual double shortest_distance(const Particle& p) const = 0; // returns the distance between p and the optimal path

		virtual bool is_on_edge(const Particle& p) const = 0;
		virtual bool is_outside(const Particle& p) const; // returns true if p is after pos_ex
		
		virtual Vector3D magnetic_field(const Vector3D& position) const = 0; // vector fields are seen as methods
		virtual Vector3D electric_field(const Vector3D& position) const = 0;
}; 

class Curved_element : public Element {
	protected :
		double const k; // curvature
	
	public :
		Curved_element(const Vector3D& entry, const Vector3D& exit, double n_radius, element_type n_type, double n_k, std::shared_ptr<Element> n_element = nullptr)
		: Element(entry, exit, n_radius, n_type, n_element), k(n_k) {}

		double shortest_distance(const Particle& p) const override;
		Vector3D curvature_center(void) const; // returns the center of curvature as a vector

		bool is_on_edge(const Particle& p) const override;
		bool is_outside(const Particle& p) const override;

		Vector3D magnetic_field(const Vector3D& position) const override; 
		Vector3D electric_field(const Vector3D& position) const override;
}; 

class Straight_element : public Element {
	public :
		Straight_element(const Vector3D& entry, const Vector3D& exit, double n_radius, element_type n_type, std::shared_ptr<Element> n_element = nullptr)
		: Element(entry, exit, n_radius, n_type, n_element) {}

		double shortest_distance(const Particle& p) const override;
		bool is_on_edge(const Particle& p) const override;
		bool is_outside(const Particle& p) const override;

		Vector3D magnetic_field(const Vector3D& position) const override; 
		Vector3D electric_field(const Vector3D& position) const override;
}; 

class Dipole : public Curved_element {
	
}; 

// note : je mettrai à jour le fichier réponse d'ici ce weekend, je voulais avoir ton avis :
// je pensais qu'il était mieux de considerer un champ comme une méthode
// la méthode shortest_distance est un plus qui sera peut être utile à l'avenir mais sinon on pourra juste la supprimer
// particle_list à developper dans le constructeur d'élement
