#include <cmath> // for pow

#include "node.h"

void Node::subdivide(void){
	type = INT;
	for(int i(0); i <= 1; ++i) for(int j(0); j <= 1; ++j) for(int k(0); k <= 1; ++k){
		children[i + 2*j + 4*k] = std::unique_ptr<Node>(new Node(domain.octant(i,j,k)));
	}
}

void Node::reset(void){
	if(type == INT){
		/* children.fill(nullptr); */
	}
	type = EMPTY;
}

bool Node::insert(Particle* my_particle){
	if(not domain.contains(*my_particle)) return false;
	switch(type){
		case INT:{
			total_charge.incorporate(*my_particle);
			for(const auto &child : children) if(child->insert(my_particle)) return true;
			return false;
		}
		case EXT:{
			// TODO handle this correctly
			if(*my_particle == *tenant) return false;

			total_charge.incorporate(*my_particle);
			subdivide();

			for(const auto &child : children) if(child->insert(tenant)) break;
			tenant = nullptr;

			for(const auto &child : children) if(child->insert(my_particle)) return true;
			return false;
		}
		case EMPTY:{
			type = EXT;
			tenant = my_particle;
			total_charge = *my_particle;
			return true;
		}
	}
}

void Node::apply_electromagnetic_force(Particle& P) const{
	if(type == EMPTY) return;
	if(type == EXT){
		P.receive_electromagnetic_force(total_charge);
		return;
	}
	// else, type == INT

	const double ratio(domain.getVolume_cube_root() / Vector3D::distance(P, total_charge));

	if(ratio <= simcst::BARNES_HUT_THETA){
		P.receive_electromagnetic_force(total_charge);
	}else{
		for(const auto &child : children){
			child->apply_electromagnetic_force(P);
		}
	}
}

void Node::print_elements(void) const{
	if(type == INT) for(const auto &child : children) child->print_elements();
	if(type == EXT){
		std::cout << *tenant << std::endl;
		std::cout << " is in\n";
		domain.print(std::cout);
	}
}

void Node::print_type(void){
	if(type == INT) std::cout << "INT\n";
	if(type == EXT) std::cout << "EXT\n";
	if(type == EMPTY) std::cout << "EMPTY\n";
}

void Node::draw_tree(void) const{
	if(type == EXT){
		domain.getCanvas()->draw(domain);
	}

	if(type == INT){
		for(const auto &child : children){
			child->draw_tree();
		}
	}
}
