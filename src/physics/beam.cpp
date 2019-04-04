#include "beam.h"
#include "particle.h"
#include "../vector3d/vector3d.h"
#include <vector>
#include <cmath>
#include <memory>

void CircularBeam::initialise(void) {
	setParticle_number(particle_number/macro_particle_factor);
	for (size_t i(0); i < particle_number; ++i){
		Particle macro_particle(reference_particle.scale(macro_particle_factor));
		Vector3D new_position;
		macro_particle.setPosition(new_position);
		particle_list.push_back(std::make_unique<Particle>(Particle(macro_particle))); 
	}
}

double Beam::average_energy(void) const{
	if (particle_number == 0) return 0.0;
	double average_energy(0.0);
	for (size_t i(0); i < particle_number; ++i){
		average_energy += particle_list[i]->energy();
	}
	return average_energy*macro_particle_factor/particle_number; 
}


Vector3D Beam::radial_average_velocity(void) const{
	Vector3D radial_average_velocity(0,0,0);
	if (particle_number == 0) return radial_average_velocity;
	for (size_t i(0); i < particle_number; ++i){
		radial_average_velocity += particle_list[i]->getVelocity(); // TODO need relative_radial_axis 
	}
	return (macro_particle_factor/particle_number) * radial_average_velocity;
}

Vector3D Beam::vertical_average_velocity(void) const{
	Vector3D vertical_average_velocity(0,0,0);
	if (particle_number == 0) return vertical_average_velocity;
	for (size_t i(0); i < particle_number; ++i){
		vertical_average_velocity += Vector3D(0,0,particle_list[i]->getVelocity()[2]); 
	}
	return (macro_particle_factor/particle_number) * vertical_average_velocity;
}

Vector3D Beam::radial_average_position(void) const{
	Vector3D radial_average_position(0,0,0);
	if (particle_number == 0) return radial_average_position;
	for (size_t i(0); i < particle_number; ++i){
		radial_average_position+= particle_list[i]->getVelocity(); // TODO need relative_radial_axis 
	}
	return (macro_particle_factor/particle_number) * radial_average_position;
}

Vector3D Beam::vertical_average_position(void) const{
	Vector3D vertical_average_position(0,0,0);
	if (particle_number == 0) return vertical_average_position; 
	for (size_t i(0); i < particle_number; ++i){
		vertical_average_position+= Vector3D(0,0,particle_list[i]->getPosition()[2]); 
	}
	return (macro_particle_factor/particle_number) * vertical_average_position;
}

double Beam::vertical_emittance(void) const{
	return sqrt((vertical_average_position()).norm2()*vertical_average_velocity().norm2() - (vertical_average_position().norm()*vertical_average_velocity().norm())*(vertical_average_position().norm()*vertical_average_velocity().norm()));
}

double Beam::radial_emittance(void) const{
	return sqrt((radial_average_position()).norm2()*radial_average_velocity().norm2() - (radial_average_position().norm()*vertical_average_velocity().norm())*(radial_average_position().norm()*radial_average_velocity().norm()));
}

std::array<double,3> Beam::radial_ellipse_coefficients(void) const{
	std::array<double,3> radial_ellipse_coefficients;
	radial_ellipse_coefficients[0] = radial_average_velocity().norm2()/radial_emittance();
	radial_ellipse_coefficients[1] = radial_average_position().norm()*radial_average_velocity().norm()/radial_emittance();
	radial_ellipse_coefficients[2] = radial_average_position().norm2()/radial_emittance();
	return radial_ellipse_coefficients;
} 

std::array<double,3> Beam::vertical_ellipse_coefficients(void) const{
	std::array<double,3> vertical_ellipse_coefficients;
	vertical_ellipse_coefficients[0] = vertical_average_velocity().norm2()/vertical_emittance();
	vertical_ellipse_coefficients[1] = vertical_average_position().norm()*vertical_average_velocity().norm()/vertical_emittance();
	vertical_ellipse_coefficients[2] = vertical_average_position().norm2()/vertical_emittance();
	return vertical_ellipse_coefficients;
} 

void Beam::evolve(double dt){
	for (size_t i(0); i < particle_number; ++i){
		particle_list[i]->evolve(dt);
	}
}
