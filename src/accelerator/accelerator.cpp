#include "accelerator.h"

void Accelerator::initialize(void){
	int N(element_list.size());
	try{
		for(int i(0); i <= N-2; ++i){
			element_list[i]->link(*element_list[i+1]);
		}
	}
	catch(...){ throw; }
}

std::ostream& Accelerator::print(std::ostream& output) const{
	output << "\nELEMENTS:\n\n";
	if(element_list.empty()) output << "   none\n";
	for(Element* E : element_list){
		output << *E << "\n\n";
	}
	output << "PARTICLES:\n\n";
	if(particle_list.empty()) output << "   none\n";
	for(Particle* P : particle_list){
		output << *P << "\n";
	}
	return output;
}

std::ostream& operator<<(std::ostream& output, const Accelerator &A){
	return A.print(output);
}

void Accelerator::setCanvas(Canvas* c){
	canvas = c;
	for(Particle* p : particle_list) p->setCanvas(c);
	for(Element* e : element_list) e->setCanvas(c);
}

void Accelerator::evolve(double dt){
	for(Element* e : element_list) e->evolve(dt);
	for(Particle* p : particle_list) p->evolve(dt);
}
