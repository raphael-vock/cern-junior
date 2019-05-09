#pragma once

#include <array>

#include "../vector3d/vector3d.h"
#include "box.h"

class Node : public Box{
	protected:
		// TODO use unique_ptr
		void subdivide(void);
		PointCharge total_charge;


	public:
		virtual ~Node(void) = 0;

		/* void reset(void); */

		virtual void apply_electromagnetic_force(Particle& P) const = 0; // recursively increments gravity on P according to Barnes-Hut approximation with parameter THETA

		/* Node(Box my_Box) : domain(my_Box), type(EMPTY), total_charge(vctr::ZERO_VECTOR, 0.0){} */

		virtual bool insert(Particle* my_Point) = 0;

		/* void print_elements(void) const; */
		/* void print_type(void); */

		/* void draw_tree(void) const; */
};

class InteriorNode : public Node{
	private:
		virtual ~InteriorNode(void) override{};
		std::array<Node*, 8> children;

	public:
		virtual bool insert(Particle* my_Point) override;
};

class ExteriorNode : public Node{
	private:
		virtual ~ExteriorNode() override{};
		Particle* tenant;

	public:
		virtual bool insert(Particle* my_Point) override;
};

class EmptyNode : public Node{
	private:
		virtual ~EmptyNode() override{};

	public:
		virtual bool insert(Particle* my_Point) override;
};
