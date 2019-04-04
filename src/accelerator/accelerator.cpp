#include "accelerator.h"

void Accelerator::weld(void){
	const int N(size());
	if(N <= 1) return;

	for(size_t i(0); i <= N-2; ++i){
		at(i)->setSuccessor(at(i+1).get());
		at(i+1)->setPredecessor(at(i).get());
	}
	back()->setSuccessor(front().get());
	front()->setPredecessor(back().get());
}

void Accelerator::addParticle(Vector3D r, Vector3D v, double mass, double charge, double radius, const RGB &color){
	for(auto &E : *this){
		if(E->contains(r)){
			std::unique_ptr<Particle> p(new Particle(canvas, r, v, mass, charge, radius, color));
			E->addParticle(p);
			return;
		}
	}
}

// TODO replace new with make_unique
void Accelerator::addStraightSection(double radius, const Vector3D &end){
	push_back(std::unique_ptr<Element>(new StraightSection(canvas, empty() ? origin : back()->getExit_point(), end, radius, time)));
	length += back()->length();
}

void Accelerator::addDipole(double radius, double curvature, double B_0, const Vector3D &end){
	push_back(std::unique_ptr<Element>(new Dipole(canvas, empty() ? origin : back()->getExit_point(), end, radius, curvature, time, B_0)));
	length += back()->length();
}

void Accelerator::addQuadrupole(double radius, double b, const Vector3D &end){
	push_back(std::unique_ptr<Element>(new Quadrupole(canvas, empty() ? origin : back()->getExit_point(), end, radius, time, b)));
	length += back()->length();
}

void Accelerator::addRadiofrequencyCavity(double radius, double curvature, double E_0, double omega, double kappa, double phi, const Vector3D &end){
	push_back(std::unique_ptr<Element>(new RadiofrequencyCavity(canvas, empty() ? origin : back()->getExit_point(), end, radius, curvature, time, E_0, omega, kappa, phi)));
	length += back()->length();
}

std::ostream& Accelerator::print(std::ostream& output, bool print_elements) const{
	if(print_elements){
		output << "\nELEMENTS:\n\n";
		if(empty()) output << "   none\n\n";
		for(auto &E : *this){
			output << *E << "\n\n";
		}
	}

	output << "PARTICLES:\n\n";
	bool no_particles(true);
	for(auto &E : *this){
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
	for(std::unique_ptr<Element> &e : *this) e->evolve(dt);
}

Vector3D Accelerator::inverse_curvilinear_coord(double s) const{
	if(length <= simcst::ZERO_DISTANCE) throw excptn::ACCELERATOR_DEGENERATE_GEOMETRY;
	assert(not empty());

	// shift s so that 0 ≤ s < length
	s = fmod(s, length);
	if(s < 0) s += length;

	std::cout << s << std::endl;

	int i(0);
	double l(at(i)->length());
	while(s > l){
		s -= l;
		++i;
		l = at(i)->length();
	}

	return at(i)->inverse_curvilinear_coord(s);
}
