#include <QMainWindow>
#include <QApplication>
#include <random>
#include <cmath>

#include "glwidget.h"
#include "vector3d.h"
#include "particle.h"
#include "universe.h"

int main(int argc, char* argv[]){
	QApplication a(argc, argv);

	Vector3D origin(-20.0,-20.0,-20.0);
	Universe Omega(origin,40,40,40);

	double M(1e3);// mass of sun
	double R(1.5);// radius of sun

	double m(0.1);// mass of asteroids
	double r(0.01);// mass of asteroids
	int N(1e4);// number of asteroids

	// creating the sun...
	/* Omega.insert( */
	/* 	0,0,0, */
	/* 	0,0,0, */
	/* 	M, */
	/* 	0.0, */
	/* 	R */
	/* ); */

	std::random_device gen;
	std::normal_distribution<double> distance(5*R, 3*R);
	std::uniform_real_distribution<double> angle(0.0, 2*M_PI);

	// asteroids...
	for(int i(1); i <= N; ++i){
		double d(distance(gen));
		double theta(angle(gen));
		Vector3D x(d*sin(theta), d*cos(theta), 0.0);
		Vector3D v(cos(theta), -sin(theta), 0.0);
		v *= sqrt(Particle::G*m*N/d);
		Omega.insert(x,v,m,0,r);
	}

	/* for(int i(1); i <= 10; ++i){ */
	/* 	double d(15*R); */
	/* 	double theta(angle(gen)); */
	/* 	Vector3D x(d*sin(theta), d*cos(theta), 0.0); */
	/* 	Vector3D v(cos(theta), -sin(theta), 0.0); */
	/* 	v *= sqrt(Particle::G*M/d); */
	/* 	Omega.insert(x,v,10000,0.0,1); */
	/* } */

	GLWidget w(nullptr, Omega);

	w.show();

	return a.exec();
	return 0;
}
