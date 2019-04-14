#pragma once

#include <array>

#include "../vector3d/vector3d.h"
#include "box.h"

class Node;// TODO is forward declaration necessary?

class Node{
	private:
		// TODO use unique_ptr
		std::array<std::unique_ptr<Node>,8> children;
		Box domain;
		Particle* tenant;

		enum node_type { INT, EXT, EMPTY };
		node_type type;

		PointCharge total_charge;        // the theoretical particle that represents the cell,
						         // i.e. its charge is the total charge of the particles in the cell
						         // and its position is their barycenter weighted by charge

	public:
		// TODO make private
		void subdivide(void);

		void reset(void);

		Box getBox(void) const{ return domain; }

		void apply_electromagnetic_force(Particle& P) const; // recursively increments gravity on P according to Barnes-Hut approximation with parameter THETA

		Node(Box my_Box) : domain(my_Box), type(EMPTY), total_charge(vctr::ZERO_VECTOR, 0.0){}

		bool insert(Particle* my_Point);

		void print_elements(void) const;
		void print_type(void);

		void draw_tree(void) const;
};
