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

	//*******************
	w.addFodoStructure(r, b, 1.0,  Vector3D(3,-2));
	w.addDipole(r,k,B, Vector3D(2,-3));
	w.addFodoStructure(r, b, 1.0,  Vector3D(-2,-3));
	w.addDipole(r,k,B, Vector3D(-3,-2));
	w.addFodoStructure(r, b, 1.0,  Vector3D(-3,2));
	w.addDipole(r,k,B, Vector3D(-2,3));
	w.addFodoStructure(r, b, 1.0,  Vector3D(2,3));
	w.addDipole(r,k,B);
	//*******************
	/* w.addCircularBeam(Electron(Vector3D(3,1.5), 1.81, Vector3D(1,1)), 1000, 1.0); */
	w.addCircularBeam(Proton(Vector3D(3,1.5), 2.0, Vector3D(1,1)), 2000, 1.0);

	w.initialize();

	w.show();

	return a.exec();
}
