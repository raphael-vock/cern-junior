#pragma once

#include <array>

#include "../vector3d/vector3d.h"
#include "box.h"

class Node;

class Node{
	private:
		std::array<Node*,8> children;
		Box domain;
		Particle* tenant;

		enum node_type { INT, EXT, EMPTY };
		node_type type;

		Particle virtual_particle; // the theoretical particle that represents the cell,
						   // i.e. its mass is the total mass of the particles in the cell
						   // and its position is their barycenter

	public:
		Node(Box my_Box) : domain(my_Box), type(EMPTY), virtual_particle(vctr::ZERO_VECTOR, vctr::ZERO_VECTOR, 0.0, 0.0){}

		void subdivide(void);
		bool insert(Particle* my_Point);

		void increment_gravity(Particle& P) const; // increments gravity on P according to Barnes-Hut approximation with parameter THETA
		void apply_gravity(Particle& P) const; // sets gravity on P

		void print_elements(void) const;
		void print_type(void);

		void info(void) const;
};
