#include <iostream> // for cout 
#include <iomanip> // for setw
#include <cmath> // for pow, asin

#include "particle.h"

using namespace std;
using namespace phcst;

void Particle::scale(double lambda){
	mass *= lambda;
	charge *= lambda;
	radius *= pow(lambda, 1.0/3.0);
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
	F_g *= G_USI * mass * P.mass / pow( F_g.norm2() + simcst::GRAVITY_SMOOTHING_EPSILON, 1.5 );
	P.F += F_g;
}

void Particle::move(double dt){
	v += ((dt/C_USI) / (gamma()*mass)) * F;
	r += dt * C_USI * v;
}

void Particle::evolve(double dt){
	move(dt);
	reset_force();
}

void Particle::add_force(const Vector3D & my_F){
	F += my_F;
}

void Particle::add_magnetic_force(const Vector3D &B, double dt){
	if(dt <= simcst::ZERO_TIME) return;
	Vector3D magnetic_force(C_USI*charge*(v^B));

	Vector3D axis(v^magnetic_force);
	double alpha(asin(dt*magnetic_force.norm()/(2*gamma()*mass*C_USI*v.norm())));
	add_force(magnetic_force.rotated(axis, alpha));
}

void Particle::add_electric_force(const Vector3D &E){
	add_force(charge*E);
}

double Particle::gamma(void) const{
	return 1.0/(sqrt(1.0 - v.norm2()));
}

double Particle::energy(void) const{
	return gamma()*mass*C2_USI;
}

ostream& Particle::print(ostream& output) const{
	int indent(25);
	output << setw(' ')
	<< setw(indent) << "Position (m)  " <<  r << "\n"
	<< setw(indent) << "Velocity (m)  " << C_USI*v << "\n"
	<< setw(indent) << "Gamma  " << gamma() << "\n"
	<< setw(indent) << "Energy (GeV)  " << 1e-9/E_USI*energy() << "\n"
	<< setw(indent) << "Mass (GeV/c^2)  " << C2_USI*1e-9/E_USI*mass << "\n"
	<< setw(indent) << "Charge (C)  " << charge << "\n"
	<< setw(indent) << "Force (N)  " << F  << "\n"
	<< "\n";
	return output; 
}

ostream& operator<<(ostream& output, const Particle &particle){
	return particle.print(output);
}      
