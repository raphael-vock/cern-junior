#ifndef NODE_H
#define NODE_H

#include <array>
#include "vector3d.h"
#include "box.h"

extern const double THETA;

class Node;

class Node{
	private:
		Particle* tenant;


		Particle virtual_particle; // the theoretical particle that represents the cell,
						   // i.e. its mass is the total mass of the particles in the cell
						   // and its position is their barycenter
	public:
		enum node_type { INT, EXT, EMPTY };
		node_type type;
		std::array<Node*,8> children;
		Box domain;
		Node(Box my_Box) : domain(my_Box), type(EMPTY), virtual_particle(){}

		void subdivide(void);
		bool insert(Particle* my_Point);

		void increment_gravity(Particle& P) const; // increments gravity on P according to Barnes-Hut approximation with parameter THETA
		void set_gravity(Particle& P) const; // sets gravity on P

		void print_elements(void) const;
		void print_type(void);

		void info(void) const;
};

#endif
