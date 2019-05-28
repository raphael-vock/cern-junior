#include "accelerator.h"
#include "beam.h"

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

void Accelerator::draw_beams(void) const{
	for(auto &b : beams) if(b) b->draw();
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

void Accelerator::addGaussianCircularBeam(const Particle &model, uint N, double lambda, double sigma_x, double sigma_v){
	beams.push_back(new GaussianCircularBeam(*this, model, N, lambda, sigma_x, sigma_v));
}

void Accelerator::addUniformCircularBeam(const Particle &model, uint N, double lambda, double sigma_x, double sigma_v){
	beams.push_back(new UniformCircularBeam(*this, model, N, lambda, sigma_x, sigma_v));
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

void Accelerator::buildPolygon(Vector3D center, uint n, double major_radius, double minor_radius, double b, double B_0){
	const double theta(2*M_PI/n);
	const double d(2.0*sin(theta/2));
	const double alpha(asin(d/(2*major_radius)));

	const double L(major_radius * 2.0 * sin(theta/2.0));

	origin = center + major_radius*Vector3D(cos(alpha), sin(alpha), 0);

	for(int k(1); k <= n; ++k){
		addFodoCell(minor_radius, b, L/4.0, center + major_radius * Vector3D(cos(theta*k - alpha), sin(theta*k - alpha), 0));

		addDipole(minor_radius, 1.0/major_radius, B_0, center + major_radius * Vector3D(cos(theta*k + alpha), sin(theta*k + alpha), 0));
	}
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

void cernjunior::build_default_accelerator(Accelerator &w){
	const double r(0.5);
	const double k(1.0);

	const double B(5.89158);
	const double b(1.2);

	w.addFodoCell(r, b, 1.0, Vector3D(3,-2));
	w.addDipole(r,k,B, Vector3D(2,-3));
	w.addFodoCell(r, b, 1.0, Vector3D(-2,-3));
	w.addDipole(r,k,B, Vector3D(-3,-2));
	w.addFodoCell(r, b, 1.0, Vector3D(-3,2));
	w.addDipole(r,k,B, Vector3D(-2,3));
	w.addFodoCell(r, b, 1.0, Vector3D(2,3));
	w.addDipole(r,k,B);
}
