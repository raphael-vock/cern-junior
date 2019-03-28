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

	Dipole D(nullptr, ZERO_VECTOR, {5.0,0.0,0.0}, 0.5, 0.1, nullptr, nullptr, 1);
	Quadrupole Q(nullptr, {-5.0,0.0,0.0}, {5.0,0.0,0.0}, 1.0, 0.1, nullptr, nullptr, 1);
	RadiofrequencyCavity E(nullptr, {0.0,0.0,0.0}, {5.0,0.0,0.0}, 2.0, 0.0, nullptr, nullptr, 1.0, 1.0, 0.4, M_PI/2);

	Accelerator A(nullptr, {&D}, {});

	cout << A << endl;

	GLWidget w(nullptr, &A);

	w.show();

	return a.exec();
}
