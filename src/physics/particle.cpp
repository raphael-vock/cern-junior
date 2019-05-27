#include <iostream> // for cout
#include <iomanip> // for setw
#include <cmath> // for pow, asin

#include "particle.h"

#include "../accelerator/element.h"

using namespace std;
using namespace phcst;

Vector3D PointCharge::electromagnetic_force(const PointCharge &Q) const{
	Vector3D F(*this - Q);
	F *= K*charge*Q.getCharge()/((gamma*Q.getGamma())*(pow(F.norm2() + simcst::SMOOTHING_CONSTANT, 1.5)));
	return F;
}

void PointCharge::incorporate(const PointCharge &P){
	const double q(P.charge);

	*this *= charge;
	/* gamma *= charge; */

	*this += q*P;
	/* gamma += q*P.gamma; */

	charge += q;

	*this *= 1.0/charge;

	// TODO what if charge is zero? would a geometric mean be more suitable?
}

const RGB Particle::getColor(void) const{
	// modulates color based on force
	return getDefaultColor()->modulate(current_element->orthogonal_offset(*this), current_element->getRadius());
}

void Particle::scale(double lambda){
	mass *= lambda;
	charge *= lambda;
}

void Particle::receive_electromagnetic_force(const PointCharge &Q){
	// TODO this must be for sufficiently large values of gamma
	if(this == &Q) return;

	add_force(Q.electromagnetic_force(*this));
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

ostream& Particle::print(ostream& output) const{
	int indent(25);

	output << "   " << particle_type() << ":\n";

	output << setw(' ')
	<< setw(indent) << "Position (m)  "; Vector3D::print(output) << "\n"
	<< setw(indent) << "Velocity (m)  " << C_USI*v << "\n"
	<< setw(indent) << "Gamma  " << gamma << "\n"
	<< setw(indent) << "Energy (GeV)  " << 1e-9/E_USI*energy << "\n"
	<< setw(indent) << "Mass (GeV/c^2)  " << C2_USI*1e-9/E_USI*mass << "\n"
	<< setw(indent) << "Charge (C)  " << charge << "\n"
	<< setw(indent) << "Force (N)  " << F  << "\n"
	<< "\n";
	return output;
}

ostream& operator<<(ostream& output, const Particle &particle){
	return particle.print(output);
}

void Particle::move(double dt){
	v += dt/(gamma*mass*phcst::C_USI) * F;
	*this += dt * phcst::C_USI * v;

	if(current_element->is_after(*this)){
		current_element = current_element->getSuccessor();
	}

	if(current_element->is_before(*this)){
		current_element = current_element->getPredecessor();
	}
}

void Particle::insert_into_tree(void){
	current_element->insert(this);
}

void Particle::evolve(double dt){
	current_element->apply_forces(*this, dt);
	move(dt);
	reset_force();
	update_attributes();
}

bool Particle::has_collided(void) const{
	return current_element->has_collided(*this);
}

Vector3D Particle::radial_vector_calculation(void) const {
	if (current_element->is_straight()) {return vctr::Z_VECTOR^current_element->direction();}
	else {Vector3D u = (*this - current_element->center()).unitary(); u -= (vctr::Z_VECTOR|u)*u; return u;}
}

double Particle::radial_position(void) const {
	return *this|radial_vector_calculation();
}

double Particle::vertical_position(void) const {
	return (*this)[2];
}

double Particle::radial_velocity(void) const {
	return v|radial_vector_calculation();
}

double Particle::vertical_velocity(void) const {
	return v[2];
}

std::unique_ptr<Particle> concrete_particle(const Vector3D &x_0, double E, const Vector3D &dir, char particle_code){
	switch(particle_code){
		case 'p': return std::unique_ptr<Particle>(new Proton(x_0, E, dir));
		case 'e': return std::unique_ptr<Particle>(new Electron(x_0, E, dir));
		default: throw excptn::UNRECOGNIZED_PARTICLE_CODE;
	}
}
