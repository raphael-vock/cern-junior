#include <QMainWindow>
#include <QApplication>
#include <random>
#include <cmath>

#include "../misc/physical_constants.h"
#include "glwidget.h"

using namespace phcst;

int main(int argc, char* argv[]){
	QApplication a(argc, argv);

	GLWidget w(nullptr);

	w.show();

	return a.exec();
	return 0;
}
