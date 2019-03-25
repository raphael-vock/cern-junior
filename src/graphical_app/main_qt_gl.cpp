#include <QMainWindow>
#include <QApplication>
#include <vector>
#include <cmath>

#include "../misc/physical_constants.h"
#include "../accelerator/element.h"
#include "../accelerator/accelerator.h"
#include "glwidget.h"

using namespace phcst;
using namespace basicvector;

int main(int argc, char* argv[]){
	std::vector<Vector3D> list;

	QApplication a(argc, argv);

	Dipole D(nullptr, ZERO_VECTOR, {1.0,0.0,0.0}, 0.5, 0.5, nullptr, 2.0);
	Quadrupole Q(nullptr, {1.0,0.0,0.0}, {2.0,0.0,0.0}, 1.0, 2.0, nullptr, 1.0);
	StraightSection S(nullptr, {2.0,0.0,0.0}, {3.0,0.0,0.0}, 1.0, nullptr);

	Accelerator A(nullptr, {&D, &Q, &S}, {});

	GLWidget w(nullptr, A);

	w.show();

	return a.exec();
}
