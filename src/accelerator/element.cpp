#include "../misc/exceptions.h"

#include "../misc/exceptions.h"
#include "element.h"
#include <algorithm>

using namespace std;
using namespace excptn;

Element::Element(
	Canvas* display,
	const Vector3D& entry,
	const Vector3D& exit,
	double my_radius,
	double my_curvature,
	std::shared_ptr<double> my_clock
) :
	Drawable(display),
	Node(Box(
			canvas,
			entry + 0.5*(exit - entry),
			0.5*(exit - entry) + (abs(my_curvature) <= simcst::ZERO_CURVATURE ? vctr::ZERO_VECTOR : my_radius*(exit-entry).unitary()),
			(abs(my_curvature) <= simcst::ZERO_CURVATURE ? my_radius : my_radius + (1.0/my_curvature)*(1.0-sqrt(abs(1.0-0.25*my_curvature*my_curvature*(exit - entry).norm2())))
	))),
	entry_point(entry),
	exit_point(exit),
	radius(my_radius),
	curvature(my_curvature),
	clock(my_clock),
	dir((exit-entry).unitary()),
	length(is_straight() ? direction().norm() : 2.0*asin(direction().norm()*curvature/2.0)/curvature)
{
	// initializing (u,v,w)
	try{
		if(is_straight()){
			u = direction().unitary();
			v = u.orthogonal();
		}else{
			Vector3D C(center());
			u = (entry_point - C).unitary();
			v = exit_point - C;
			try{
				v = (v - (v|u)*u).unitary();
			}
			catch(std::exception){
				v = (u^vctr::Z_VECTOR).unitary();
			}
		} 
		w = u^v;
	}
	catch(std::exception){ throw excptn::ELEMENT_DEGENERATE_GEOMETRY; }
}

void Element::apply_forces(Particle &p, double dt) const{
	apply_lorentz_force(p, dt);
	apply_electromagnetic_force(p);
}

bool Element::is_straight(void) const{
	return abs(curvature) <= simcst::ZERO_CURVATURE;
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

Vector3D Element::center(void) const{
	if(is_straight()) throw ZERO_CURVATURE_CENTER;
	Vector3D direction(exit_point - entry_point);

	try{
		return 0.5*(entry_point + exit_point) + (1.0/curvature)*sqrt(abs(1.0-0.25*curvature*curvature*direction.norm2()))*(direction^vctr::Z_VECTOR).unitary();
	}
	catch(std::exception){
		// an exception is thrown if direction is parallel to z-vector which is prohibited
		throw ELEMENT_DEGENERATE_GEOMETRY;
	}
}

Vector3D Element::direction(void) const{
	return exit_point - entry_point;
}

Vector3D Element::relative_coords(const Vector3D &x) const{
	return x - entry_point;
}

Vector3D Element::local_coords(const Vector3D &x) const{
	Vector3D y(relative_coords(x));
	return y - (y|u)*u;
}

double Element::curvilinear_coord(const Vector3D &x) const{
	double l(relative_coords(x)|dir);
	return is_straight() ? l : asin(l*curvature) / curvature;
}

bool Element::has_collided(const Vector3D &r) const{
	if(is_straight()){
		return local_coords(r).norm() >= radius;
	}else{
		const Vector3D X(r - center());
		try{
			const Vector3D u((X - r[2]*vctr::Z_VECTOR).unitary());
			return (X - (1.0/abs(curvature))*u).norm() >= radius;
		}
		catch(std::exception){
			// means that the point is directly over the center
			return true;
		}
	}
}

bool Element::is_after(const Vector3D &r) const{
	Vector3D rel(relative_coords(r));
	Vector3D D(direction());
	return (rel|D) > D.norm2();
}

bool Element::is_before(const Vector3D &r) const{
	Vector3D rel(relative_coords(r));
	return (rel|dir) < 0.0;
}

std::ostream& StraightSection::print(std::ostream& output) const{
	output << "Straight section:\n";
	Element::print(output);
	return output;
}

void MagneticElement::apply_lorentz_force(Particle& p, double dt) const{
	p.add_magnetic_force(B(p, *clock), dt);
}

void ElectricElement::apply_lorentz_force(Particle& p, double dt) const{
	p.add_electric_force(E(p, *clock));
}

// FIELD EQUATIONS
Vector3D Dipole::B(const Vector3D &x, double) const{
	return B_0 * vctr::Z_VECTOR;
}

Vector3D Quadrupole::B(const Vector3D &x, double) const{
	Vector3D y(local_coords(x));
	Vector3D u(vctr::Z_VECTOR ^ direction().unitary());
	return b*((y|u)*vctr::Z_VECTOR + x[2]*u);
}

Vector3D RadiofrequencyCavity::E(const Vector3D &x, double t) const{
	return E_0*sin(omega*t - kappa*curvilinear_coord(x) + phi) * dir;
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
	cout << "\n   RFC Parameters : (E,ω,κ,Φ) = " << '(' << E_0 << ", " << omega << ", " << kappa << ", " << phi << ')';
	return output;
}

Vector3D Element::inverse_curvilinear_coord(double s) const{
	if(is_straight())
		return entry_point + s*direction().unitary();
	if(s*s < simcst::ZERO_DISTANCE)
		return entry_point;
	else{
		double beta(s*curvature);
		return center() + (1.0/abs(curvature))*(cos(beta)*u + sin(beta)*v);
	}
}

Vector3D Element::local_trajectory(double s) const{
	if(is_straight()) return dir;

	double beta(s*curvature);
	return -sin(beta)*u + cos(beta)*v;
}

// MAX FORCES

double StraightSection::maxForce(const Particle &p) const{
	return 0.0;
}

double Dipole::maxForce(const Particle &p) const{
	return abs(p.getCharge() * B_0);
}

double Quadrupole::maxForce(const Particle &p) const{
	return abs(p.getCharge() * b * sqrt(length*length + radius*radius)* phcst::C_USI);
}

double RadiofrequencyCavity::maxForce(const Particle &p) const{
	return abs(p.getCharge() * E_0);
}
