#pragma once

#include <vector>

#include "../vector3d/vector3d.h"
#include "particle.h"
#include "node.h"

class Universe{
	private:
		std::vector<Particle*> particle_list;
		Box domain;
		Node tree;
	public:
		int particle_count = 0;

		Universe(Box my_domain) : domain(my_domain), tree(my_domain){}
		Universe(Vector3D origin, double x, double y, double z) : domain(Box(origin, x, y, z)), tree(domain){}
		
		void insert(double x, double y, double z, double v_x = 0.0, double v_y = 0.0, double v_z = 0.0, double my_mass = Particle::DEFAULT_MASS, double my_charge = 0.0, double my_radius = Particle::DEFAULT_RADIUS);

		void insert(Vector3D x_0 = Vector3D::ZERO_VECTOR, Vector3D v_0 = Vector3D::ZERO_VECTOR, double my_mass = Particle::DEFAULT_MASS, double my_charge = 0.0, double my_radius = Particle::DEFAULT_RADIUS);

		std::vector<Particle*>* getParticle_list(void);
		
		/* void set_gravity(void); */
		void direct_sum(void);

		void evolve(double dt);

		void print_particles(void) const;
		void print_tree(void) const;
};
