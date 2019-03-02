#include <QApplication>
#include <QMainWindow>
#include <random>
#include <cmath>

#include "glwidget.h"
#include "vector3d.h"
#include "particle.h"

int main(int argc, char* argv[]){
	QApplication a(argc, argv);

	Universe my_universe;

	double M(1000.0);// mass of sun
	double R(1.5);// radius of sun

	double av_m(0.05);// mass of asteroids
	int N(500);// number of asteroids

	double p_r(0.6);// radius of planets
	double p_m(5);// mass of planets
	int n(5);// number of planets

	// creating the sun...
	my_universe.new_particle(
		0,0,0,
		0,0,0,
		M,
		R,
		{1.0,0.0,0.0}
	);

	std::random_device gen;
	std::uniform_real_distribution<double> distance(5*R, 12*R);
	std::uniform_real_distribution<double> mass(av_m, 2*av_m);

	// asteroids...
	for(int i(1); i <= N; ++i){
		double d(distance(gen));
		double m(mass(gen));

		Vector3D x_0(random_unit_vector());
		x_0 *= d;

		Vector3D h(random_unit_vector());

		Vector3D v_0(h ^ x_0);
		if(v_0 != 0){
			double v(sqrt(G*M/d));
			v_0 *= (v/v_0.norm());
			my_universe.new_particle(x_0, v_0, m, m/3);
		}

		m *= 2;
		d *= 2;
		x_0 *= 2;
		h *= 2;// scramble these so they're shuffled on the next loop
	}

	// planets...
	for(int i(0); i <= n; ++i){
		double d(distance(gen));

		Vector3D x_0(random_unit_vector());
		x_0 *= d;

		Vector3D h(random_unit_vector());

		Vector3D v_0(h ^ x_0);
		if(v_0 != 0){
			double v(sqrt(G*M/d));
			v_0 *= (v/v_0.norm());
			my_universe.new_particle(x_0, v_0, p_m, p_r, {0.0,0.0,1.0});
		}

		x_0 *= 2;
		h *= 2;// scramble these so they're shuffled on the next loop
	}

	GLWidget w(nullptr, my_universe);
	w.setUniverse(my_universe);

	w.show();

	return a.exec();
}
