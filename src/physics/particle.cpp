#include <iostream> // for cout 
#include <iomanip> // for setw
#include <cmath> // for pow, asin

#include "particle.h"

using namespace std;
using namespace phcst;

void Particle::scale(double lambda){
	mass *= lambda;
	charge *= lambda;
}

void Particle::incorporate(const Particle& P){
	const double q(P.charge);

	r *= charge;
	v *= charge;

	r += q*P.r;
	v += q*P.r;

	charge += q;

	// TODO what if charge is zero?
	r *= 1.0/charge;

	// TODO would a geometric mean be more suitable?
}

void Particle::apply_electromagnetic_force(Particle& P) const{
	// TODO this must be for sufficiently large values of gamma 
	
	if(this == &P) return;
	if(abs(charge) <= simcst::ZERO_CHARGE) return;

	Vector3D F_g(r - P.r);

	F_g *= phcst::K*charge*charge/((gamma*gamma)*(F_g.norm2() + simcst::SMOOTHING_CONSTANT));

	P.add_force(F_g);
}

void Particle::move(double dt){
	v += dt/(gamma*mass*C_USI) * F;
	r += dt * C_USI * v;
}

void Particle::evolve(double dt){
	move(dt);
	reset_force();

	update_gamma();
}

void Particle::add_force(const Vector3D & my_F){
	F += my_F;
}

void Particle::add_magnetic_force(const Vector3D &B, double dt){
	if(dt <= simcst::ZERO_TIME) return;
	Vector3D magnetic_force(C_USI*charge*(v^B));

	Vector3D axis(v^magnetic_force);
	double alpha(asin(dt*magnetic_force.norm()/(2*gamma*mass*C_USI*v.norm())));
	add_force(magnetic_force.rotated(axis, alpha));
}

void Particle::add_electric_force(const Vector3D &E){
	add_force(charge*E);
}

void Particle::update_gamma(void){
	gamma = 1.0/(sqrt(1.0 - v.norm2()));
}

double Particle::energy(void) const{
	return gamma*mass*C2_USI;
}

ostream& Particle::print(ostream& output) const{
	int indent(25);

	output << "   " << particle_type() << ":\n";

	output << setw(' ')
	<< setw(indent) << "Position (m)  " <<  r << "\n"
	<< setw(indent) << "Velocity (m)  " << C_USI*v << "\n"
	<< setw(indent) << "Gamma  " << gamma << "\n"
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
