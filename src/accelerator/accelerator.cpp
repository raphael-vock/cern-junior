#include "accelerator.h"

void Accelerator::weld(void){
	const int N(element_list.size());
	if(N <= 1) return;

	for(size_t i(0); i <= N-2; ++i){
		element_list[i]->setSuccessor(element_list[i+1].get());
		element_list[i+1]->setPredecessor(element_list[i].get());
	}
	element_list.back()->setSuccessor(element_list.front().get());
	element_list.front()->setPredecessor(element_list.back().get());
}

void Accelerator::addParticle(Vector3D r, Vector3D v, double mass, double charge, double radius, const RGB &color){
	for(auto &E : element_list){
		if(E->contains(r)){
			std::unique_ptr<Particle> p(new Particle(canvas, r, v, mass, charge, radius, color));
			E->addParticle(p);
			return;
		}
	}
}

void Accelerator::addStraightSection(Vector3D start, Vector3D end, double radius){
	element_list.push_back(std::unique_ptr<Element>(new StraightSection(canvas, start, end, radius, time)));
}

void Accelerator::addDipole(Vector3D start, Vector3D end, double radius, double curvature, double B_0){
	element_list.push_back(std::unique_ptr<Element>(new Dipole(canvas, start, end, radius, curvature, time, B_0)));
}

void Accelerator::addQuadrupole(Vector3D start, Vector3D end, double radius, double b){
	element_list.push_back(std::unique_ptr<Element>(new Quadrupole(canvas, start, end, radius, time, b)));
}

void Accelerator::addRadiofrequencyCavity(Vector3D start, Vector3D end, double radius, double curvature, double E_0, double omega, double kappa, double phi){
	element_list.push_back(std::unique_ptr<Element>(new RadiofrequencyCavity(canvas, start, end, radius, curvature, time, E_0, omega, kappa, phi)));
}

std::ostream& Accelerator::print(std::ostream& output){
	output << "\nELEMENTS:\n\n";
	if(element_list.empty()) output << "   none\n\n";
	for(auto &E : element_list){
		output << *E << "\n\n";
	}
	output << "PARTICLES:\n\n";
	bool no_particles(true);
	for(auto &E : element_list){
		if(E->print_elements(output)) no_particles = false;
	}
	if(no_particles) output << "   none\n\n";

	return output;
}

std::ostream& operator<<(std::ostream& output, Accelerator &A){
	return A.print(output);
}

void Accelerator::evolve(double dt){
	*time += dt;
	for(std::unique_ptr<Element> &e : element_list) e->evolve(dt);
}
