#include "particle.h"

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

const Vector3D* Particle::getPosition(void) const{
	return &r;
}

const Vector3D* Particle::getVelocity(void) const{
	return &v;
}

Vector3D Particle::getMomentum(void) const{
	return mass * v;
}

const Vector3D* Particle::getForce(void) const{
	return &F;
}

void Particle::resetForce(void){
	F = ZERO_VECTOR;
}

bool Particle::is_touching(const Particle& q) const{
	return distance(r, q.r) <= radius + q.radius;
}

void Particle::barycenter(const Particle& P){
	r *= mass;
	r += P.mass * (*P.getPosition());
	mass += P.mass;
	r *= 1/mass;
	r_p = r;
}

void Particle::increment_gravity(Particle& P) const{
	if(not alive) return;
	if(P.r == r) return;

	Vector3D F_g(r - P.r);
	F_g *= Particle::G * mass * P.mass / pow( F_g.norm2() + EPSILON_SQUARED, 1.5 );
	P.F += F_g;
}

void Particle::evolve(double dt){
	double f(F.norm()/(1e5*G*EPSILON_SQUARED)); // == F/F_max
	double e((v.norm())/12);
	color = {f, f, 1};
	std::swap(v, v_p);
	v = v_p + (dt / mass) * F;

	std::swap(r, r_p);
	r = r_p + (dt * v);
}

void Particle::swallow(Particle q){
	double q_mass(q.getMass());
	v *= mass;
	v += q_mass*(*q.getVelocity());

	r *= mass;
	r += q_mass*(*q.getPosition());

	mass += q_mass;

	v *= 1/mass;
	r *= 1/mass;

	radius = pow( pow(radius,3.0) + pow(q.getRadius(),3.0), 0.333 );
}
