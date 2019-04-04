#include "../misc/exceptions.h"

#include "../misc/exceptions.h"
#include "element.h"

using namespace std;
using namespace excptn;

void Element::addParticle(std::unique_ptr<Particle> &p){
	particle_list.push_back(move(p));
	++ number_of_particles;
}

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

bool Element::print_elements(std::ostream& output) const{
	// returns true iff there is at least one element
	for(auto &p : particle_list){
		p->print(output);
		output << "\n";
	}
	return not particle_list.empty();
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
	try{
		Vector3D y(relative_coords(x));
		Vector3D d(direction().unitary());
		return y - (y|d)*d;
	}
	catch(std::exception){
		throw ELEMENT_DEGENERATE_GEOMETRY;
	}
}

double Element::curvilinear_coord(const Vector3D &x) const{
	double l((local_coords(x) - relative_coords(x))|direction().unitary());
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
	Vector3D dir(direction());
	return (rel|dir) > dir.norm2();
}

bool Element::is_before(const Vector3D &r) const{
	Vector3D rel(relative_coords(r));
	Vector3D dir(direction());
	return (rel|dir) < 0.0;
}

bool Element::contains(const Vector3D &r) const{
	return not is_after(r) and not is_before(r) and not has_collided(r);
}

void Element::evolve(double dt){
	for(int i(0); i <= number_of_particles-1;){
		add_lorentz_force(*particle_list[i], dt);
		/* if(successor) successor->add_lorentz_force(*particle_list[i], dt); */
		/* if(predecessor) predecessor->add_lorentz_force(*particle_list[i], dt); */

		/* std::cout << particle_list[i]->getForce() << std::endl; */
		particle_list[i]->evolve(dt);
		
		if(is_after(*particle_list[i])){
			if(successor) successor->addParticle(particle_list[i]);
			particle_list.erase(particle_list.begin()+i);
			-- number_of_particles;
		}else if(is_before(*particle_list[i])){
			if(predecessor) predecessor->addParticle(particle_list[i]);
			particle_list.erase(particle_list.begin()+i);
			-- number_of_particles;
		}else if(has_collided(*particle_list[i])){
			particle_list.erase(particle_list.begin()+i);
			-- number_of_particles;
		}else{
			++i;
		}
	}
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
	Vector3D u(vctr::Z_VECTOR ^ direction().unitary());
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
	cout << "\n   RFC Parameters : (E,ω,κ,Φ) = " << '(' << E_0 << ", " << omega << ", " << kappa << ", " << phi << ')';
	return output;
}

Vector3D Element::inverse_curvilinear_coord(double s) const{
	if (s*s < simcst::ZERO_DISTANCE) return entry_point;
	if (is_straight()) return s*direction().unitary();
	else {
		Vector3D C(center());
		Vector3D u((entry_point - C).unitary());
		Vector3D v(exit_point - C);
		try {
			v = (v - (v|u)*u).unitary();
		} catch(std::exception) {
			try {
				v = (u^vctr::Z_VECTOR).unitary();
			} catch(std::exception) {throw excptn::ELEMENT_DEGENERATE_GEOMETRY;}
		} 
		double beta = s*curvature; 
		return C + (1/abs(curvature))*(cos(beta)*u + sin(beta)*v);
	}
}
