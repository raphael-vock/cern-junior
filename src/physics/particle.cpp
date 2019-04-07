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
	F_g *= G_CGS * mass * P.mass / pow( F_g.norm2() + simcst::GRAVITY_SMOOTHING_EPSILON, 1.5 );
	P.F += F_g;
}

void Particle::move(double dt){
	// For this calculation we need to convert mass from natural units to c.g.s.
	// 1 GeV/c^2 = 1.7826619 x 10-24 g

	v += (dt / (gamma()*mass)) * F ;
	r += dt * v;
}

void Particle::evolve(double dt){
	move(dt);
	reset_force();
}

void Particle::swallow(Particle& q){
	double q_mass(q.getMass());
	// TODO check units

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
	Vector3D normalized_magnetic_force(charge*(v^B)); // missing c factor

	Vector3D axis((C2_CGS*v)^normalized_magnetic_force);
	double alpha(asin(dt*normalized_magnetic_force.norm()/(2*gamma()*mass*v.norm())));
	add_force(normalized_magnetic_force.rotated(axis, alpha));
}

void Particle::add_electric_force(const Vector3D &E){
	add_force(charge*E);
}

double Particle::gamma(void) const{
	return 1.0/(sqrt(1.0 - v.norm2()));
}

double Particle::energy(void) const{
	return gamma()*mass*C2_CGS;
}

ostream& Particle::print(ostream& output) const{
	int indent(25);
	output << setw(' ')
	<< setw(indent) << "Position (m)  " <<  1e-2*r << "\n"
	<< setw(indent) << "Velocity (m)  " << 1e-2*C_CGS*v << "\n"
	<< setw(indent) << "Gamma  " << gamma() << "\n"
	<< setw(indent) << "Energy (GeV)  " << energy()/(1e-4*C_CGS*GEV_CGS) << "\n"
	<< setw(indent) << "Mass (GeV/c^2)  " << GEV_C2_CGS*mass << "\n"
	<< setw(indent) << "Charge (C)  " << C_CHARGE_CGS * charge << "\n"
	<< setw(indent) << "Force (N)  " << 1e5*F  << "\n"
	<< "\n";
	return output; 
}

ostream& operator<<(ostream& output, const Particle &particle){
	return particle.print(output);
}      
