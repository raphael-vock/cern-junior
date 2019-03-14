#include <thread>
#include "universe.h"

std::vector<Particle>* Universe::getParticle_list(void){
	return &particle_list;
}

void Universe::insert(double x, double y, double z, double v_x, double v_y, double v_z, double my_mass, double my_charge, double my_radius){
	particle_list.push_back(Particle(x,y,z,v_x,v_y,v_z,my_mass,my_charge,my_radius));
	tree.insert(&particle_list.back());
	++N;
}

void Universe::insert(Vector3D x_0, Vector3D v_0, double my_mass, double my_charge, double my_radius){
	particle_list.push_back(Particle(x_0,v_0,my_mass,my_charge,my_radius));
	tree.insert(&particle_list.back());
	++N;
}

// naive gravity algorithm:
/* void Universe::direct_sum(void){ */
/* 	for(auto &p : particle_list) for(const auto &q : particle_list) q.increment_gravity(p); */
/* } */

void Universe::evolve(double dt){
	// empty tree:
	tree = Node(domain);

	// refresh tree:
	for(Particle& particle : particle_list) if(particle.alive) tree.insert(&particle);


	for(Particle& particle : particle_list){
		if(particle.alive){
			tree.set_gravity(particle);
			particle.evolve(dt);
		}
	}
	
}

void Universe::print_tree(void) const{
	tree.print_elements();
}

void Universe::print_particles(void) const{
	for(size_t i(0); i <= N-1; ++i){
		std::cout << "-------------\nParticle " << i+1 << ": ";
		std::cout << particle_list[i] << std::endl;
		std::cout << "F = " << *particle_list[i].getForce() << "\n";
	}
}
