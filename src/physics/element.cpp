#include "../vector3d/vector3d.h"
#include "particle.h"
#include "element.h"
#include <cmath>

Vector3D Element::getPos_en(void) const{
	return pos_en;
}
Vector3D Element::getPos_ex(void) const{
	return pos_ex;
}
double Element::getRadius(void) const{
	return radius;
}

//===================================

double Straight::shortest_distance(const Particle& p) const{ // we use heron's rule to find the height of the triangle p - pos_en -pos_ex 
	double s = ((getPos_en() - p.getPosition()).norm() + (p.getPosition() - getPos_ex()).norm() + (getPos_ex() - getPos_en()).norm()); 
	return (2/(getPos_ex() - getPos_en()).norm()) * sqrt(s * (s- (getPos_en() - p.getPosition()).norm()) * (s- (p.getPosition() - getPos_ex()).norm()) * (s- (getPos_ex() - getPos_en()).norm()));
}

//===================================

Vector3D Curve::curv_center(void) const{
	Vector3D e3(0, 0, 1);
	return 0.5 * (getPos_en() + getPos_ex()) + (1/k) * sqrt(1 - pow(k, 2) * (getPos_ex() - getPos_en()).norm2()/4) * (getPos_ex() - getPos_en()).unitary() ^ e3;
}

bool Straight::collision_edge(const Particle& p) const{
	return ((p.getPosition() - getPos_en()) - ((p.getPosition() - getPos_en()) | (getPos_ex() - getPos_en()).unitary()) * (getPos_ex() - getPos_en()).unitary()).norm() > getRadius();
}

bool Curve::collision_edge(const Particle& p) const{
	Vector3D x = p.getPosition() - curv_center();
	Vector3D e3(0,0,1);
	return (x - (1/k) * (x - x.getCoords()[2]*e3)).norm() > getRadius();
}
