#include "../vector3d/vector3d.h"
#include "particle.h"
#include "element.h"
#include <cmath>

Vector3D Element::getEntry_point(void) const{
	return entry_point;
}
Vector3D Element::getExit_point(void) const{
	return exit_point;
}
double Element::getRadius(void) const{
	return radius;
}

//===================================

double Straight::shortest_distance(const Particle& p) const{ // we use heron's rule to find the height of the triangle p - pos_en -pos_ex 
	double s = ((getEntry_point() - p.getPosition()).norm() + (p.getPosition() - getExit_point()).norm() + (getExit_point() - getEntry_point()).norm()); 
	return (2/(getExit_point() - getEntry_point()).norm()) * sqrt(s * (s- (getEntry_point() - p.getPosition()).norm()) * (s- (p.getPosition() - getExit_point()).norm()) * (s- (getExit_point() - getEntry_point()).norm()));
}

//===================================

Vector3D Curve::curvature_center(void) const{
	Vector3D e3(0, 0, 1);
	return 0.5 * (getEntry_point() + getExit_point()) + (1/k) * sqrt(1 - pow(k, 2) * (getExit_point() - getEntry_point()).norm2()/4) * (getExit_point() - getEntry_point()).unitary() ^ e3;
}

bool Straight::collision_edge(const Particle& p) const{
	return ((p.getPosition() - getEntry_point()) - ((p.getPosition() - getEntry_point()) | (getExit_point() - getEntry_point()).unitary()) * (getExit_point() - getEntry_point()).unitary()).norm() > getRadius();
}

bool Curve::collision_edge(const Particle& p) const{
	Vector3D x = p.getPosition() - curvature_center();
	Vector3D e3(0,0,1);
	return (x - (1/k) * (x - x.getCoords()[2]*e3)).norm() > getRadius();
}
