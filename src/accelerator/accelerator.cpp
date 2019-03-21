#include "accelerator.h"

std::ostream& Accelerator::print(std::ostream& output) const{
	output << "\nELEMENTS:\n\n";
	for(Element* E : element_list){
		output << *E << "\n";
	}
	output << "\nPARTICLES:\n\n";
	for(Particle* P : particle_list){
		output << *P << "\n";
	}
	return output;
}

std::ostream& operator<<(std::ostream& output, const Accelerator &A){
	return A.print(output);
}
