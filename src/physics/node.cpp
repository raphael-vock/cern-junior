#include "node.h"

const double THETA(0.5);

void Node::subdivide(void){
	type = INT;
	children[0] = new Node(domain.octant(0,0,0));
	children[1] = new Node(domain.octant(0,0,1));
	children[2] = new Node(domain.octant(0,1,0));
	children[3] = new Node(domain.octant(0,1,1));
	children[4] = new Node(domain.octant(1,0,0));
	children[5] = new Node(domain.octant(1,0,1));
	children[6] = new Node(domain.octant(1,1,0));
	children[7] = new Node(domain.octant(1,1,1));
}

bool Node::insert(Particle* my_particle){
	if(not domain.contains(*my_particle)) return false;
	switch(type){
		case INT:{
			virtual_particle.barycenter(*my_particle);
			for(Node* child : children) if(child->insert(my_particle)) return true;
			return false;
		}
		case EXT:{
			if(tenant->alive){
				if(my_particle->is_touching(*tenant)){
					my_particle->swallow(*tenant);
					return insert(my_particle);
				}

				virtual_particle.barycenter(*my_particle);
				subdivide();

				for(Node* child : children) if(child->insert(tenant)) break;
				tenant = nullptr;

				for(Node* child : children) if(child->insert(my_particle)) return true;
				return false;
			}
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
		virtual_particle.increment_gravity(P);
		return;
	}

	double ratio(pow(domain.volume(),0.333) / distance(*P.getPosition(), *virtual_particle.getPosition()) );

	if(ratio <= THETA) virtual_particle.increment_gravity(P);
	else for(Node* child : children) child->increment_gravity(P);
}

void Node::set_gravity(Particle& P) const{
	P.resetForce();
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
	std::cout << *virtual_particle.getPosition() << std::endl;
	std::cout << "Total mass = " << virtual_particle.getMass() << "\n";
}
