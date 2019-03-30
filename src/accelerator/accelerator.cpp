#include "accelerator.h"

void Accelerator::initialize(Canvas* c){
	canvas = c;

	for(Particle* p : particle_list){
		p->setCanvas(c);
		for(std::unique_ptr<Element> &e : element_list) e->insert(*p);
	}

	for(std::unique_ptr<Element> &e : element_list){
		e->setCanvas(c);
	}
}

void Accelerator::addParticle(Vector3D r, Vector3D v, double mass, double charge, double radius){
	// TODO
}

void Accelerator::addStraightSection(Vector3D start, Vector3D end, double radius){
	element_list.push_back(std::unique_ptr<Element>(new StraightSection(canvas, start, end, radius, time)));
}

void Accelerator::addDipole(Vector3D start, Vector3D end, double radius, double curvature, double B_0){
	element_list.push_back(std::unique_ptr<Element>(new Dipole(canvas, start, end, radius, curvature, time, B_0)));
}

void Accelerator::addQuadrupole(Vector3D start, Vector3D end, double radius, double curvature, double b){
	element_list.push_back(std::unique_ptr<Element>(new Quadrupole(canvas, start, end, radius, curvature, time, b)));
}

std::ostream& Accelerator::print(std::ostream& output){
	output << "\nELEMENTS:\n\n";
	if(element_list.empty()) output << "   none\n";
	for(std::unique_ptr<Element> &E : element_list){
		output << *E << "\n\n";
	}
	output << "PARTICLES:\n\n";
	if(particle_list.empty()) output << "   none\n";
	for(Particle* P : particle_list){
		output << *P << "\n";
	}
	return output;
}

std::ostream& operator<<(std::ostream& output, Accelerator &A){
	return A.print(output);
}

void Accelerator::evolve(double dt){
	time += dt;
	for(std::unique_ptr<Element> &e : element_list) e->evolve(dt);
	for(Particle* p : particle_list) p->evolve(dt);
}
