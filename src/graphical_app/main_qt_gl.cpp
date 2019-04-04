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

	GLWidget w(nullptr, Vector3D(0,0,0));

	w.addQuadrupole(1.0, 1.0, Vector3D(4,0,0));

	w.addDipole(1.0, -0.5, -0.12, Vector3D(6,2,0));
	w.addDipole(1.0, -0.5, -0.12, Vector3D(4,4,0));

	/* w.addQuadrupole(1.0, 1.0, Vector3D(0,4,0)); */
	w.addRadiofrequencyCavity(1.0, 0.0, 0.1, 1.0, 1.0, 0.0, Vector3D(0,4,0));

	w.addDipole(1.0, -0.5, -0.12, Vector3D(-2,2,0));
	w.addDipole(1.0, -0.5, -0.12, Vector3D(0,0,0));

	w.weld();

	w.addParticle(Vector3D(0,0,0), Vector3D(2,0,0), 0.5, 3.9855, 0.1, RGB::YELLOW);
	w.addParticle(Vector3D(1,0,0), Vector3D(2,0,0), 0.5, 3.9855, 0.1, RGB::YELLOW);

	w.print(cout);

	w.show();

	return a.exec();
}
