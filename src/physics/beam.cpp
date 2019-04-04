#include "../misc/exceptions.h"
#include "beam.h"

double Beam::mean_energy(void) const{
	double mean(0.0);
	for(const auto &p : *this){
		mean += p->energy();
	}
	return N ? (lambda/N) * mean : 0.0;
}

Vector3D Beam::mean_position(void) const{
	double radial(0.0);
	double vertical(0.0);
	for(const auto &p : *this){
		radial += p->getPosition()[0]; // TODO project on local trajectory
		vertical += p->getPosition()[1];
	}
	Vector3D mean(radial, vertical);
	return N ? (lambda/N)*mean : mean;
}

Vector3D Beam::mean_velocity(void) const{
	double radial(0.0);
	double vertical(0.0);
	for(const auto &p : *this){
		radial += p->getVelocity()[0]; // TODO project on local trajectory
		vertical += p->getVelocity()[1];
	}
	Vector3D mean(radial, vertical);
	return N ? (lambda/N)*mean : mean;
}

double Beam::vertical_emittance(void) const{
	// TODO
}

double Beam::radial_emittance(void) const{
	// TODO
}

std::array<double,3> Beam::radial_ellipse_coefficients(void) const{
	// TODO
} 

std::array<double,3> Beam::vertical_ellipse_coefficients(void) const{
	// TODO
} 

void Beam::evolve(double dt){
	for(const auto &p : *this){
		p->evolve(dt);
	}
}

void Circular_beam::initialize(void) {
	if(lambda < simcst::ZERO_LAMBDA) throw excptn::ZERO_LAMBDA;
	for(size_t i(0); i < N/lambda; ++i){
		push_back(std::unique_ptr<Particle>(new Particle(reference_particle.scale(lambda))));
	}
}

