#include "../misc/exceptions.h"
#include "beam.h"


Beam::Beam(Accelerator& machine, const Particle &p, uint number_of_particles, double my_lambda) :
	Drawable(machine.getCanvas()),
	model_particle(p.copy()),
	N(number_of_particles / my_lambda),
	lambda(my_lambda),
	habitat(&machine)
{
	if(my_lambda <= simcst::ZERO_LAMBDA) throw excptn::ZERO_LAMBDA;
}

void Beam::update(void){
	// TODO
}

double Beam::mean_energy(void) const{
	double mean(0.0);
	for(const auto &p : *this){
		mean += (*p)->getEnergy();
	}
	return N ? (lambda/N) * mean : 0.0;
}

double Beam::vertical_emittance(void) const{
	unsigned int n(0); // denotes the number of particles for mean calculation
	double r(0.0); // denotes the sum over position coordinate square
	double vr(0.0); // denotes the sum over velocity coordinate squared
	double rvr(0.0); // denotes the sum over the product of velocity and position coordinate

	for (auto const& p : *this) {
		double position = (*p)->vertical_position();
		r += position*position;
		double velocity = (*p)->vertical_velocity();
		vr += velocity*velocity;
		rvr += position*velocity;
		++n;
	}
	r /= n;
	vr /= n;
	rvr /= n;
	return r + vr + rvr;
}

double Beam::radial_emittance(void) const{
	unsigned int n(0);
	double r(0.0);
	double vr(0.0);
	double rvr(0.0);

	for (auto const& p : *this) {
		double position = (*p)->radial_position();
		r += position*position;
		double velocity = (*p)->radial_velocity();
		vr += velocity*velocity;
		rvr += position*velocity;
		++n;
	}
	if(n == 0) return 0;

	r /= n;
	vr /= n;
	rvr /= n;
	return r + vr + rvr;
}

double Beam::mean_radial_position_squared(void) const {
	unsigned int n(0);
	double r(0.0);

	for (auto const& p : *this) {
		double position = (*p)->radial_position();
		r += position*position;
		++n;
	}
	return n ? r/n : 0.0;
}
double Beam::mean_vertical_position_squared(void) const {
	unsigned int n(0);
	double r(0.0);

	for (auto const& p : *this) {
		double position = (*p)->vertical_position();
		r += position*position;
		++n;
	}
	return n ? r/n : 0.0;
}

double Beam::mean_radial_velocity_squared(void) const {
	unsigned int n(0);
	double r(0.0);

	for (auto const& p : *this) {
		double position = (*p)->radial_velocity();
		r += position*position;
		++n;
	}
	return n ? r/n : 0.0;
}
double Beam::mean_vertical_velocity_squared(void) const {
	unsigned int n(0);
	double r(0.0);

	for (auto const& p : *this) {
		double position = (*p)->vertical_velocity();
		r += position*position;
		++n;
	}
	return n ? r/n : 0.0;
}

double Beam::mean_radial_product(void) const {
	unsigned int n(0);
	double r(0.0);

	for (auto const& p : *this) {
		double position = (*p)->radial_position();
		double velocity = (*p)->radial_velocity();
		r += position*velocity;
		++n;
	}
	return n ? r/n : 0.0;
}

double Beam::mean_vertical_product(void) const {
	unsigned int n(0);
	double r(0.0);

	for (auto const& p : *this) {
		double position = (*p)->vertical_position();
		double velocity = (*p)->vertical_velocity();
		r += position*velocity;
		++n;
	}
	return n ? r/n : 0.0;
}

std::array<double,3> Beam::radial_ellipse_coefficients(void) const{
	double emittance = radial_emittance();
	return std::array<double,3> {
		mean_radial_velocity_squared()/emittance, // A11
		mean_radial_product()/(-emittance), // A12
		mean_radial_position_squared()/emittance // A22
	};
}

std::array<double,3> Beam::vertical_ellipse_coefficients(void) const{
	double emittance = vertical_emittance();
	return std::array<double,3> {
		mean_vertical_velocity_squared()/emittance, // A11
		mean_vertical_product()/(-emittance), // A12
		mean_vertical_position_squared()/emittance // A22
	};
}

std::ostream& Beam::print(std::ostream& output) const{
	output << "Model particle:\n" << *model_particle;
	// TODO
	return output;
}

void CircularBeam::activate(){
	if(N == 0) return;

	double l(habitat->getLength());
	double h(l / N);

	const double v(model_particle->getVelocity().norm());
	for(size_t i(1); i <= N; ++i){
		std::array<Vector3D,2> position_and_trajectory(habitat->position_and_trajectory(i*h));

		std::unique_ptr<Particle> copy(model_particle->copy());

		copy->setPosition(position_and_trajectory[0]);
		copy->setVelocity((model_particle->getCharge() >= 0 ? v : -v)*position_and_trajectory[1]);
		copy->scale(lambda);

		habitat->addParticle(*copy);
	}
	shrink_to_fit(); // deallocate redundant memory
}
