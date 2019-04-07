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

	w.addCircularBeam(Proton(Vector3D(3.00984, -0.391837), 2.0, Vector3D(1,0)), 5000, 1);

	w.weld();
	w.activate();

	w.show();

	return a.exec();
}
