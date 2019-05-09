#include "accelerator.h"
#include "../physics/beam.h"

void Accelerator::weld(void){
	const int N(size());
	if(N <= 1) return;

	for(size_t i(0); i <= N-2; ++i){
		if((*this)[i]->getExit_point() != (*this)[i+1]->getEntry_point()){
			throw excptn::NON_MATCHING_LINK_POINTS;
		}
		(*this)[i]->setSuccessor((*this)[i+1].get());
		(*this)[i+1]->setPredecessor((*this)[i].get());
	}
	back()->setSuccessor(front().get());
	front()->setPredecessor(back().get());
}

void Accelerator::activate(void){
	for(auto &b : beams){
		b->activate();
	}
}

void Accelerator::initialize(void){
	weld();
	activate();
}

void Accelerator::draw_elements(void) const{
	for(auto &e : *this) e->draw();
}

void Accelerator::draw_particles(void) const{
	for(auto &p : particles) if(p) p->draw();
}

void Accelerator::addParticle(const Particle &to_copy){
	for(auto &E : *this){
		if(E->contains(to_copy)){
			particles.push_back(to_copy.copy());
			particles.back()->setElement(E.get());
			particles.back()->setCanvas(canvas);
			return;
		}
	}
}

void Accelerator::addCircularBeam(const Particle &model, uint N, double lambda){
	beams.push_back(new CircularBeam(*this, model, N, lambda));
}

void Accelerator::addStraightSection(double radius, const Vector3D &end){
	push_back(std::unique_ptr<Element>(new StraightSection(canvas, empty() ? origin : back()->getExit_point(), end, radius, time)));
	length += back()->getLength();
}

void Accelerator::addDipole(double radius, double curvature, double B_0, const Vector3D &end){
	push_back(std::unique_ptr<Element>(new Dipole(canvas, empty() ? origin : back()->getExit_point(), end, radius, curvature, time, B_0)));
	length += back()->getLength();
}

void Accelerator::addQuadrupole(double radius, double b, const Vector3D &end){
	push_back(std::unique_ptr<Element>(new Quadrupole(canvas, empty() ? origin : back()->getExit_point(), end, radius, time, b)));
	length += back()->getLength();
}

void Accelerator::addFodoCell(double radius, double b, double L, const Vector3D &end){
	Vector3D start(empty() ? origin : back()->getExit_point());
	double l((end - start).norm()/2.0 - L);
	if(l <= 0.0) throw excptn::ELEMENT_DEGENERATE_GEOMETRY;

	try{
		Vector3D dir((end-start).unitary());

		// Focusing quadrupole:
		addQuadrupole(radius, b, start + l*dir);
		// First straight section:
		addStraightSection(radius, start + (L+l)*dir);
		// Defocusing quadrupole:
		addQuadrupole(radius, -b, start + (L+2.0*l)*dir);
		// Second straight section:
		addStraightSection(radius, end);
	}
	catch(std::exception){ throw excptn::ELEMENT_DEGENERATE_GEOMETRY; }
}

void Accelerator::addRadiofrequencyCavity(double radius, double E_0, double omega, double kappa, double phi, const Vector3D &end){
	push_back(std::unique_ptr<Element>(new RadiofrequencyCavity(canvas, empty() ? origin : back()->getExit_point(), end, radius, time, E_0, omega, kappa, phi)));
	length += back()->getLength();
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
	for(const auto &p : particles){
		p->print(output);
	}
	if(particles.empty()) output << "   none\n\n";

	return output;
}

std::ostream& operator<<(std::ostream& output, Accelerator &A){
	return A.print(output);
}

void Accelerator::evolve(double dt){
	*time += dt;

	for(auto &e : *this){
		e->reset();
	}

	int particle_count(particles.size());
	for(int i(0); i < particle_count;){
		if(particles[i]->has_collided()){
			std::swap(particles[i], particles.back());
			particles.pop_back();
			--particle_count;
			// note: this clause is O(1)
		}else{
			particles[i]->insert_into_tree();
			++i;
		}
	}

	for(auto &p : particles){
		if(p) p->evolve(dt);
	}
}

std::array<Vector3D,2> Accelerator::position_and_trajectory(double s) const{
	if(length <= simcst::ZERO_DISTANCE) throw excptn::ACCELERATOR_DEGENERATE_GEOMETRY;

	// shift s so that 0 ≤ s < length
	s = fmod(s, length);
	if(s < 0) s += length;

	int i(0);
	double l((*this)[i]->getLength());
	while(s > l){
		s -= l;
		++i;
		l = (*this)[i]->getLength();
	}

	return {(*this)[i]->inverse_curvilinear_coord(s), (*this)[i]->local_trajectory(s)};
}
