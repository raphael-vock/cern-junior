#include <iostream> // for std::cout 
#include <cmath> // for pow

#include "particle.h"

using namespace phcst;

int GRAVITATIONAL_SINGULARITY(1);

double Particle::getMass(void) const{
	return mass;
}

void Particle::setMass(double my_mass){
	mass = my_mass;
}

double Particle::getRadius(void) const{
	return radius;
}

RGB Particle::getColor(void) const{
	return color;
}

Vector3D Particle::getPosition(void) const{
	return r;
}

Vector3D Particle::getVelocity(void) const{
	return v;
}

Vector3D Particle::getForce(void) const{
	return F;
}

double Particle::getCharge(void) const{
	return charge;
}

void Particle::reset_force(void){
	F = Vector3D::ZERO_VECTOR;
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

void Particle::add_gravitational_force(Particle& P) const{
	if(this == &P or not alive) return;

	Vector3D F_g(r - P.r);
	F_g *= G * mass * P.mass / pow( F_g.norm2() + GRAVITY_EPSILON, 1.5 );
	P.F += F_g;
}

void Particle::evolve(double dt){
	double f(F.norm()/(G*mass*mass/GRAVITY_EPSILON)); // == F/F_max
	if(f > 1.0) f = 1.0;
	color = {0.1+f, 0.3+f*f*f, 1.0};

	v += (dt / (gamma()*mass)) * F;
	r += dt * v;

	reset_force();
}

void Particle::swallow(Particle& q){
	double q_mass(q.getMass());

	v *= mass;
	v += q_mass*(q.getVelocity());

	r *= mass;
	r += q_mass*(q.getPosition());

	mass += q_mass;

	v *= ETA/mass;
	r *= 1.0/mass;

	radius = pow( pow(radius,3.0) + pow(q.getRadius(),3.0), 1.0/3.0 );

	q.alive = false;
}

void Particle::add_force(const Vector3D & my_F){
	F += my_F;
}

void Particle::add_magnetic_force(const Vector3D &B, double dt){
	if(dt <= ZERO_TIME) return;
	Vector3D magnetic_force(charge*(v^B));
	Vector3D axis(v^magnetic_force);
	if(not axis.is_zero()){
		magnetic_force.rotate(axis,asin(dt*magnetic_force.norm()/(2*gamma()*mass*v.norm())));
	}
	add_force(magnetic_force);
}

double Particle::gamma(void) const{
	return 1.0/(sqrt(1.0-v.norm2()/(C*C)));
}

double Particle::energy(void) const{
	return gamma()*mass*C*C;
}

std::ostream& operator<<(std::ostream& output, Particle const& particle){                 
	output << "  Position : " << particle.getPosition()
	<< "\n  Velocity : " << particle.getVelocity()
	<< "\n  Energy (GeV) : " << particle.energy()/GeV
	<< "\n  Gamma : " << particle.gamma()
	<< "\n  Mass (GeV/c^2) : " << particle.getMass() * (C*C/GeV)
	<< "\n  Charge : " << particle.getCharge()
	<< "\n  Force : " << particle.getForce()
	<< std::endl;
	return output; 
}      
