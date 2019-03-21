#include "../vector3d/vector3d.h"
#include "../physics/particle.h"
#include "element.h"
#include <cmath>

using namespace basicvector;

/* Vector3D Element::getEntry_point(void) const{ */
/* 	return entry_point; */
/* } */
/* Vector3D Element::getExit_point(void) const{ */
/* 	return exit_point; */
/* } */
/* double Element::getRadius(void) const{ */
/* 	return radius; */
/* } */

/* double Straight_element::shortest_distance(const Particle& p) const{ // we use Heron's rule to find the height of the triangle p - entry_point - exit_point */
/* 	double s = ((entry_point - p.getPosition()).norm() + (p.getPosition() - exit_point).norm() + (exit_point - entry_point).norm()); */ 
/* 	return (2.0/(exit_point - entry_point).norm()) * sqrt(s * (s- (entry_point - p.getPosition()).norm()) * (s- (p.getPosition() - exit_point).norm()) * (s- (exit_point - entry_point).norm())); */
/* } */

Vector3D Element::center(void) const{
	if(isinf(curvature)) throw 4;
	Vector3D direction(exit_point - entry_point);
	return 0.5*(entry_point + exit_point) + (1.0/curvature)*sqrt(1.0-curvature*curvature*direction.norm2()/4.0)*(direction.unitary()^Z_VECTOR);
}

bool Element::has_collided(const Particle& p) const{
	if(isinf(curvature)){
		Vector3D r(p.getPosition() - center()); // position relative to center
		return (r - 1.0/abs(curvature)*(r - r[2]*Z_VECTOR)).norm2() >= radius*radius;
	}else{
		Vector3D d((exit_point - entry_point).unitary());
		Vector3D r(p.getPosition() - entry_point); // position relative to entry point
		return (r - (r|d)*d).norm2() >= radius*radius;
	}
}

void Element::add_lorentz_force(Particle &p) const{
	p.add_force(lorentz_force(p));
}

bool Element::has_left(const Particle& p) const{
	return Vector3D::mixed_prod(Z_VECTOR, p.getPosition(), entry_point) >= 0;
}

Vector3D Electric_element::lorentz_force(const Particle& p) const{
	return p.getCharge() * E(p.getPosition());
}

Vector3D Magnetic_element::lorentz_force(const Particle& p) const{
	return p.getCharge() * (p.getVelocity() ^ B(p.getPosition()));
}
