#include "../misc/exceptions.h"

#include "element.h"

using namespace std;
using namespace excptn;

bool Element::is_straight(void) const{
	return abs(curvature) <= simcst::ZERO_DISTANCE;
}

std::ostream& Element::print(std::ostream& output) const{
	cout << "   Entry point: " << entry_point
	     << "\n   Exit point: " << exit_point
	     << "\n   Chamber radius: " << radius
	     << "\n   Curvature: " << curvature;
	if(not is_straight()){
		cout << "\n   Center of curvature: " << center();
	}
	return output;
}

std::ostream& operator<<(std::ostream& output, const Element &E){
	return E.print(output);
}

void Element::link(Element &next_element){
	if(exit_point != next_element.entry_point) throw NON_MATCHING_LINK_POINTS;
	successor = &next_element;
}

void Element::insert(Particle &p){
	particle_list.push_back(std::unique_ptr<Particle>(&p));
}

Vector3D Element::center(void) const{
	if(is_straight()) throw ZERO_CURVATURE_CENTER;
	Vector3D direction(exit_point - entry_point);
	return 0.5*(entry_point + exit_point) + (1.0/curvature)*sqrt(1.0-0.25*curvature*curvature*direction.norm2())*(direction.unitary()^vctr::Z_VECTOR);
}

Vector3D Element::direction(void) const{
	return exit_point - entry_point;
}

Vector3D Element::unit_direction(void) const{
	return direction().unitary();
}

Vector3D Element::relative_coords(const Vector3D &x) const{
	return x - entry_point;
}

Vector3D Element::local_coords(const Vector3D &x) const{
	Vector3D y(relative_coords(x));
	return y - (y|direction())*y;
}

double Element::curvilinear_coord(const Vector3D &x) const{
	double l((local_coords(x) - relative_coords(x)) | unit_direction());
	return is_straight() ? l : asin(l*curvature) / curvature;
}

std::vector<Vector3D> Element::sample_points(void) const{
	// we want the sample points of an element to be evenly distributed on the circle of its entry surface
	// i.e. a circle orthogonal to exit_point - entry_point and with radius that of the element (i.e. Element::radius)
	std::vector<Vector3D> list;

	Vector3D u(direction());

	// constructs an orthonormal pair of vector {v,w} in the plane of the circle
	Vector3D v(u.orthogonal());
	Vector3D w(u.unitary()^v);

	int number_of_points(2*M_PI*radius*simcst::FIELD_LINE_SAMPLE_POINT_DENSITY);

	for(int i(1); i <= number_of_points; ++i){
		double theta(i / (radius*simcst::FIELD_LINE_SAMPLE_POINT_DENSITY));
		Vector3D P(entry_point + sin(theta)*v + cos(theta)*w);
		list.push_back(P + entry_point);
		list.push_back(P + exit_point);
		list.push_back(P + 0.5*(exit_point - entry_point));
	}
	return list;
}

bool Element::has_collided(const Particle& p) const{
	if(is_straight()){
		Vector3D r(p.getPosition() - center()); // position relative to center
		return (r - 1.0/abs(curvature)*(r - r[2]*vctr::Z_VECTOR)).norm2() >= radius*radius;
	}else{
		Vector3D d(unit_direction());
		Vector3D r(p.getPosition() - entry_point); // position relative to entry point
		return (r - (r|d)*d).norm2() >= radius*radius;
	}
}

bool Element::has_left(const Particle& p) const{
	return Vector3D::mixed_prod(vctr::Z_VECTOR, p.getPosition(), entry_point) >= 0;
}

void Element::evolve(double dt){
	// TODO write
}

std::ostream& StraightSection::print(std::ostream& output) const{
	output << "Straight section:\n";
	Element::print(output);
	return output;
}

void Magnetic_element::add_lorentz_force(Particle& p, double dt) const{
	p.add_magnetic_force(B(p.getPosition(), *clock), dt);
}

void Electric_element::add_lorentz_force(Particle& p, double dt) const{
	p.add_electric_force(E(p.getPosition(), *clock));
}

// FIELD EQUATIONS
Vector3D Dipole::B(const Vector3D &x, double) const{
	return B_0 * vctr::Z_VECTOR;
}

Vector3D Quadrupole::B(const Vector3D &x, double) const{
	Vector3D y(local_coords(x));
	Vector3D u(vctr::Z_VECTOR ^ direction());
	return b*((y|u)*vctr::Z_VECTOR + x[2]*u);
}

Vector3D RadiofrequencyCavity::E(const Vector3D &x, double t) const{
	// TODO work out how to calculate direction properly
	Vector3D axis((exit_point - entry_point).unitary());
	return E_0*sin(omega*t - kappa * curvilinear_coord(x) + phi) * axis;
}

// PRINTING METHODS
std::ostream& Dipole::print(std::ostream& output) const{
	output << "Dipole:\n";
	Element::print(output);
	cout << "\n   Magnetic amplitude: B_0 = " << B_0;
	return output;
}

std::ostream& Quadrupole::print(std::ostream& output) const{
	output << "Quadrupole:\n";
	Element::print(output);
	cout << "\n   Quadrupole parameter: b = " << b;
	return output;
}

std::ostream& RadiofrequencyCavity::print(std::ostream& output) const{
	output << "Radiofrequency cavity:\n";
	Element::print(output);
	cout << "\n   RFC Parameters : (E,ω,k,Φ) = " << '(' << E_0 << ", " << omega << ", " << kappa << ", " << phi << ')';
	return output;
}
