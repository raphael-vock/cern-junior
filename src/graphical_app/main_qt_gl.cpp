#include <QMainWindow>
#include <QApplication>
#include <random>
#include <cmath>

#include "glwidget.h"
#include "../vector3d/vector3d.h"
#include "../physics/particle.h"
#include "../physics/physical_constants.h"

using namespace phcst;

int main(int argc, char* argv[]){
	QApplication a(argc, argv);

	GLWidget w(nullptr);

	w.show();

	return a.exec();
	return 0;
}
