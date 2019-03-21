#include "../vector3d/vector3d.h"
#include "../physics/particle.h"

#include <cmath>

#include "element.h"

using namespace basicvector;
using namespace excptn;

void Element::link(Element &next_element){
	if(exit_point != next_element.entry_point) throw NON_MATCHING_LINK_POINTS;
	successor = &next_element;
}

Vector3D Element::center(void) const{
	if(isinf(curvature)) throw INFINITE_CURVATURE_CENTER;
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
