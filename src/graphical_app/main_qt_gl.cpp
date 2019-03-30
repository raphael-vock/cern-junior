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
	w.addStraightSection(Vector3D(-1,0,0), Vector3D(0,0,0), 0.3);
	w.addStraightSection(Vector3D(0,0,0), Vector3D(1,1,0), 0.3);
	w.print(cout);

	w.show();

	return a.exec();
}
