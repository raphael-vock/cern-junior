#include <iostream> // for std::cout 
#include <cmath> // for pow, asin

#include "particle.h"

using namespace phcst;

Particle Particle::scale(double lambda) const{
	if(lambda < 0.0) lambda = 0.0;
	return Particle(canvas, r, v, lambda*mass, lambda*charge, pow(lambda, 1.0/3.0)*radius);
}

bool Particle::is_touching(const Particle& q) const{
	return Vector3D::distance(r, q.r) <= radius + q.radius;
}

void Particle::average_particle(const Particle& P){
	r *= mass;
	r += P.mass * P.r;
	mass += P.mass;
	r *= 1.0/mass;
}

void Particle::apply_gravitational_force(Particle& P) const{
	if(this == &P) return;

	// TODO check units
	Vector3D F_g(r - P.r);
	F_g *= phcst::G * mass * P.mass / pow( F_g.norm2() + simcst::GRAVITY_SMOOTHING_EPSILON, 1.5 );
	P.F += F_g;
}

void Particle::move(double dt){
	v += (dt / (gamma()*mass)) * F;
	r += dt * v;
}

void Particle::evolve(double dt){
	move(dt);
	reset_force();
}

void Particle::swallow(Particle& q){
	double q_mass(q.getMass());

	v *= mass;
	v += q_mass*(q.getVelocity());

	r *= mass;
	r += q_mass*(q.getPosition());

	mass += q_mass;

	v *= simcst::COLLISION_ETA/mass;
	r *= 1.0/mass;

	radius = pow( pow(radius,3.0) + pow(q.getRadius(),3.0), 1.0/3.0 );
}

void Particle::add_force(const Vector3D & my_F){
	F += my_F;
}

void Particle::add_magnetic_force(const Vector3D &B, double dt){
	if(dt <= simcst::ZERO_TIME) return;
	Vector3D magnetic_force(charge*(v^B));
	Vector3D axis(v^magnetic_force);
	double alpha(asin(dt*magnetic_force.norm()/(2*gamma()*mass*v.norm())));
	add_force(magnetic_force.rotated(axis, alpha));
}

void Particle::add_electric_force(const Vector3D &E){
	add_force(charge*E);
}

double Particle::gamma(void) const{
	return 1.0/(sqrt(1.0 - v.norm2() / (phcst::C * phcst::C)));
}

double Particle::energy(void) const{
	return gamma()*mass*phcst::C*phcst::C;
}

std::ostream& Particle::print(std::ostream& output) const{
	output << "   Position: " << r
	<< "\n   Velocity: " << v
	<< "\n   Gamma: " << gamma()
	<< "\n   Energy (GeV): " << energy()*1e-9/E
	<< "\n   Mass (GeV/c^2): " << mass*(C*C*1e-9/E)
	<< "\n   Charge: " << charge
	<< "\n   Force: " << F
	<< std::endl;
	return output; 
}

std::ostream& operator<<(std::ostream& output, const Particle &particle){
	return particle.print(output);
}      
