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

double Particle::getCharge(void) const{
	return charge;
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
	if(this == &P or not alive) return;

	Vector3D F_g(r - P.r);
	F_g *= Particle::G * mass * P.mass / pow( F_g.norm2() + EPSILON_SQUARED, 1.5 );
	P.F += F_g;
}

void Particle::evolve(double dt){
	double f(F.norm()/(G*mass*mass/EPSILON_SQUARED)); // == F/F_max
	if(f > 1) f = 1;
	color = {f, f*f*f, 1};

	std::swap(v, v_p);
	v = v_p + (dt / mass) * F;

	std::swap(r, r_p);
	r = r_p + (dt * v);
	resetForce();
}

void Particle::swallow(Particle& q){
	double q_mass(q.getMass());

	v *= mass;
	v += q_mass*(*q.getVelocity());

	r *= mass;
	r += q_mass*(*q.getPosition());

	mass += q_mass;

	v *= ETA/mass;
	r *= 1/mass;

	radius = pow( pow(radius,3.0) + pow(q.getRadius(),3.0), 0.333 );

	q.alive = false;
}

void Particle::incrementForce(const Vector3D & my_F){
	F += my_F;
}

void Particle::addMagneticForce(const Vector3D & B, double dt){
	if (F.is_zero() and dt > 1e-19) {incrementForce(charge * (v^B));}
	else if (dt > 1e-19){
		incrementForce(charge * (v^B).rotate(v^F, asin(dt * F.norm()/(2*gamma() * mass * v.norm()))));
	}
}

double Particle::gamma(void) const{
	return 1/(sqrt(1-v.norm2()/pow(C, 2)));
}

double Particle::energy(void) const{
	return this->gamma() * mass * pow(C, 2);
}

std::ostream& operator<<(std::ostream& output, Particle const& particle){                 
	output << "Mass (GeV/c^2) : " << particle.getMass() * (pow(Particle::C, 2)/Particle::GeV) * 2<< std::endl 
	<< "Position : " << *(particle.getPosition()) << std::endl
	// << "Radius : " << particle.getRadius() << std::endl
	<< "Charge : " << particle.getCharge() << std::endl
	// << "Color : " << particle.getColor()[0] << " " << particle.getColor()[1] << " " << particle.getColor()[2] << std::endl
	<< "Force : " << *(particle.getForce()) << std::endl
	<< "Energy (GeV) : " << particle.energy() *1/Particle::GeV << std::endl
	<< "Gamma : " << particle.gamma();
	return output; 
}      
