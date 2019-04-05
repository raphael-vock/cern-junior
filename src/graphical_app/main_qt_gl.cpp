#include <QMainWindow>
#include <QApplication>
#include <vector>
#include <cmath>

#include "glwidget.h"

using namespace std;

using namespace phcst;
using namespace vctr;

int main(int argc, char* argv[]){
	QApplication a(argc, argv);

	GLWidget w(nullptr, Vector3D(3,2,0));

	const double r(0.5);
	const double k(1.0);

	const double B(5.89158);
	const double b(1.2);

	const double dt(1e-3);

	//*******************
	w.addQuadrupole(r,b,Vector3D(3,1));
	w.addStraightSection(r,Vector3D(3,0));
	w.addQuadrupole(r,-b,Vector3D(3,-1));
	w.addStraightSection(r,Vector3D(3,-2));

	w.addDipole(r,k,B, Vector3D(2,-3));

	w.addQuadrupole(r,b,Vector3D(1,-3));
	w.addStraightSection(r,Vector3D(0,-3));
	w.addQuadrupole(r,-b,Vector3D(-1,-3));
	w.addStraightSection(r,Vector3D(-2,-3));

	w.addDipole(r,k,B, Vector3D(-3,-2));

	w.addQuadrupole(r,b,Vector3D(-3,-1));
	w.addStraightSection(r,Vector3D(-3,0));
	w.addQuadrupole(r,-b,Vector3D(-3,1));
	w.addStraightSection(r,Vector3D(-3,2));

	w.addDipole(r,k,B, Vector3D(-2,3));

	w.addQuadrupole(r,b,Vector3D(-1,3));
	w.addStraightSection(r,Vector3D(0,3));
	w.addQuadrupole(r,-b,Vector3D(1,3));
	w.addStraightSection(r,Vector3D(2,3));

	w.addDipole(r,k,B);

	w.addCircularBeam( Particle(nullptr, Vector3D(0,0), Vector3D(2.64e8,0), E*1e9/(C*C) * 0.938272, 1.60217653e-19, 0.02, RGB::BLUE), 1000, 1.0 );
	/* for(double x(0.0); x <= 24; x += 0.4){ */
	/* 	auto thing(w.position_and_trajectory(x)); */
	/* 	w.addParticle( thing[0], Vector3D(0, -2.64754e8), E*1e9/(C*C) * 0.938272, 1.60217653e-19, 0.08, RGB::BLUE); */
	/* 	std::cout << thing[1] << std::endl; */
	/* } */

	w.weld();
	w.activate();
	w.print(std::cout);

	w.show();

	return a.exec();
}
