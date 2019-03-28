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
	std::vector<Vector3D> list;

	QApplication a(argc, argv);

	Dipole D(nullptr, ZERO_VECTOR, {5.0,0.0,0.0}, 0.5, 0.1, nullptr, nullptr, 3.14);
	Quadrupole Q(nullptr, {0.0,0.0,0.0}, {5.0,0.0,0.0}, 1.0, 0.1, nullptr, nullptr, 10.0);
	RadiofrequencyCavity E(nullptr, {0.0,0.0,0.0}, {5.0,0.0,0.0}, 2.0, 0.0, nullptr, nullptr, 1.0, 1.0, 0.4, 0.0);

	Accelerator A(nullptr, {&Q}, {});
	cout << A << endl;

	GLWidget w(nullptr, &A);

	w.show();

	return a.exec();
}
