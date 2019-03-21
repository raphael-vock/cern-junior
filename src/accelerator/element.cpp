#include "../vector3d/vector3d.h"
#include "../physics/particle.h"
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

double Straight_element::shortest_distance(const Particle& p) const{ // we use Heron's rule to find the height of the triangle p - entry_point - exit_point
	double s = ((entry_point - p.getPosition()).norm() + (p.getPosition() - exit_point).norm() + (exit_point - entry_point).norm()); 
	return (2.0/(exit_point - entry_point).norm()) * sqrt(s * (s- (entry_point - p.getPosition()).norm()) * (s- (p.getPosition() - exit_point).norm()) * (s- (exit_point - entry_point).norm()));
}

//===================================

Vector3D Curved_element::curvature_center(void) const{
	Vector3D e3(0.0, 0.0, 1.0);
	return 0.5 * (entry_point + exit_point) + (1/k) * sqrt(1 - k*k * (exit_point - entry_point).norm2()/4.0) * (exit_point - entry_point).unitary() ^ e3;
}

bool Straight_element::is_on_edge(const Particle& p) const{
	return ((p.getPosition() - entry_point) - ((p.getPosition() - entry_point) | (exit_point - entry_point).unitary()) * (exit_point - entry_point).unitary()).norm() > radius;
}

bool Curved_element::is_on_edge(const Particle& p) const{
	Vector3D e3(0.0,0.0,1.0);
	return ((p.getPosition() - curvature_center()) - (1.0/k) * (p.getPosition() - curvature_center()) - (p.getPosition() - curvature_center())[2]*e3).norm() > radius; 
}

bool Curved_element::is_outside(const Particle& p) const{
	Vector3D e3(0.0,0.0,1.0);
	return Vector3D::mixed_prod(e3, p.getPosition(), exit_point) > 0;
}

bool Straight_element::is_outside(const Particle& p) const{
	Vector3D e3(0.0,0.0,1.0);
	return Vector3D::mixed_prod(e3, p.getPosition(), exit_point) > 0;
}
