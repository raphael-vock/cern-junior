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

	double M(100.0);// mass of sun
	double R(1.0);// radius of sun
	double r(0.04);// radius of asteroids
	double m(0.075);// mass of asteroids
	double max_distance(10.0);// max distance of asteroids from sun
	int N(600);// number of asteroids

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

	for(int i(0); i <= N; ++i){
		double d(distance(gen));

		Vector3D x_0(random_unit_vector());
		x_0 *= d;

		Vector3D h(random_unit_vector());

		Vector3D v_0(h ^ x_0);
		if(v_0 != 0){
			double v(sqrt(G*M/d));
			v_0 *= (v/v_0.norm());
			my_universe.new_particle(x_0, v_0, m, r);
		}

		x_0 *= 2;
		h *= 2;// scramble these so they're shuffled on the next loop
	}

	GLWidget w(nullptr, my_universe);
	w.setUniverse(my_universe);

	w.show();

	return a.exec();
}
