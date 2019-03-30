#include <cmath> // for pow
#include <assert.h>

#include "node.h"

void Node::subdivide(void){
	type = INT;
	for(uint8_t i(0); i <= 1; ++i) for(uint8_t j(0); j <= 1; ++j) for(uint8_t k(0); k <= 1; ++k){
		children[i + 2*j + 4*k] = new Node(domain.octant(i,j,k));
	}
}

bool Node::insert(Particle* my_particle){
	assert(my_particle);
	if(not domain.contains(*my_particle)) return false;
	switch(type){
		case INT:{
			virtual_particle.average_particle(*my_particle);
			for(Node* child : children) if(child->insert(my_particle)) return true;
			return false;
		}
		case EXT:{
			virtual_particle.average_particle(*my_particle);
			subdivide();

			for(Node* child : children) if(child->insert(tenant)) break;
			tenant = nullptr;

			for(Node* child : children) if(child->insert(my_particle)) return true;
			return false;
		}
		case EMPTY:{
			type = EXT;
			tenant = my_particle;
			virtual_particle = *my_particle;
			return true;
		}
	}
	throw 0;
}

void Node::increment_gravity(Particle& P) const{
	if(type == EMPTY) return;
	if(type == EXT){
		virtual_particle.add_gravitational_force(P);
		return;
	}

	double ratio(pow(domain.volume(),1.0/3.0) / Vector3D::distance(P.getPosition(), virtual_particle.getPosition()) );

	if(ratio <= simcst::BARNES_HUT_THETA) virtual_particle.add_gravitational_force(P);
	else for(Node* child : children) child->increment_gravity(P);
}

void Node::set_gravity(Particle& P) const{
	P.reset_force();
	increment_gravity(P);
}

void Node::print_elements(void) const{
	if(type == INT) for(Node* child : children) child->print_elements();
	if(type == EXT){
		std::cout << *tenant << std::endl;
		std::cout << " is in\n";
		domain.print();
	}
}
void Node::print_type(void){
	if(type == INT) std::cout << "INT\n";
	if(type == EXT) std::cout << "EXT\n";
	if(type == EMPTY) std::cout << "EMPTY\n";
}

void Node::info(void) const{
	std::cout << "Node info:\n";
	std::cout << virtual_particle.getPosition() << std::endl;
	std::cout << "Total mass = " << virtual_particle.getMass() << "\n";
}
