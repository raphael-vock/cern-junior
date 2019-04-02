#include <QMainWindow>
#include <QApplication>
#include <vector>
#include <cmath>

#include "glwidget.h"

#include "accelerator.h"

using namespace std;

using namespace phcst;
using namespace vctr;

int main(int argc, char* argv[]){
	QApplication a(argc, argv);

	GLWidget w(nullptr);

	w.addQuadrupole(Vector3D(3, 2, 0), Vector3D(3, 1, 0), 0.1, 1.2);
	w.addStraightSection(Vector3D(3, 1, 0), Vector3D(3, 0, 0), 0.1);
	w.addQuadrupole(Vector3D(3, 0, 0), Vector3D(3, -1, 0), 0.1, -1.2);
	w.addStraightSection(Vector3D(3, -1, 0), Vector3D(3, -2, 0), 0.1);
	w.addDipole(Vector3D(3, -2, 0), Vector3D(2, -3, 0), 0.1, 1, 5.89158);
	w.addQuadrupole(Vector3D(2, -3, 0), Vector3D(1, -3, 0), 0.1, 1.2);
	w.addStraightSection(Vector3D(1, -3, 0), Vector3D(0, -3, 0), 0.1);
	w.addQuadrupole(Vector3D(0, -3, 0), Vector3D(-1, -3, 0), 0.1, -1.2);
	w.addStraightSection(Vector3D(-1, -3, 0), Vector3D(-2, -3, 0), 0.1);
	w.addDipole(Vector3D(-2, -3, 0), Vector3D(-3, -2, 0), 0.1, 1, 5.89158);
	w.addQuadrupole(Vector3D(-3, -2, 0), Vector3D(-3, -1, 0), 0.1, 1.2);
	w.addStraightSection(Vector3D(-3, -1, 0), Vector3D(-3, 0, 0), 0.1);
	w.addQuadrupole(Vector3D(-3, 0, 0), Vector3D(-3, 1, 0), 0.1, -1.2);
	w.addStraightSection(Vector3D(-3, 1, 0), Vector3D(-3, 2, 0), 0.1);
	w.addDipole(Vector3D(-3, 2, 0), Vector3D(-2, 3, 0), 0.1, 1, 5.89158);
	w.addQuadrupole(Vector3D(-2, 3, 0), Vector3D(-1, 3, 0), 0.1, 1.2);
	w.addStraightSection(Vector3D(-1, 3, 0), Vector3D(0, 3, 0), 0.1);
	w.addQuadrupole(Vector3D(0, 3, 0), Vector3D(1, 3, 0), 0.1, -1.2);
	w.addStraightSection(Vector3D(1, 3, 0), Vector3D(2, 3, 0), 0.1);
	w.addDipole(Vector3D(2, 3, 0), Vector3D(3, 2, 0), 0.1, 1, 5.89158);

	w.print(cout);

	w.show();

	return a.exec();
}
