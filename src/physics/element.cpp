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

double Straight_element::shortest_distance(const Particle& p) const{ // we use Heron's rule to find the height of the triangle p - pos_en -pos_ex 
	double s = ((getEntry_point() - p.getPosition()).norm() + (p.getPosition() - getExit_point()).norm() + (getExit_point() - getEntry_point()).norm()); 
	return (2.0/(getExit_point() - getEntry_point()).norm()) * sqrt(s * (s- (getEntry_point() - p.getPosition()).norm()) * (s- (p.getPosition() - getExit_point()).norm()) * (s- (getExit_point() - getEntry_point()).norm()));
}

//===================================

Vector3D Curved_element::curvature_center(void) const{
	Vector3D e3(0.0, 0.0, 1.0);
	return 0.5 * (getEntry_point() + getExit_point()) + (1/k) * sqrt(1 - k*k * (getExit_point() - getEntry_point()).norm2()/4.0) * (getExit_point() - getEntry_point()).unitary() ^ e3;
}

bool Straight_element::is_on_edge(const Particle& p) const{
	return ((p.getPosition() - getEntry_point()) - ((p.getPosition() - getEntry_point()) | (getExit_point() - getEntry_point()).unitary()) * (getExit_point() - getEntry_point()).unitary()).norm() > getRadius();
}

bool Curved_element::is_on_edge(const Particle& p) const{
	Vector3D x = p.getPosition() - curvature_center();
	Vector3D e3(0.0,0.0,1.0);
	return (x - (1.0/k) * (x - x[2]*e3)).norm() > getRadius();
}
