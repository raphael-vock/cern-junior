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
	w.addStraightSection(Vector3D(0,2,0), Vector3D(5,2,0), 0.5);
	w.addStraightSection(Vector3D(0,1,0), Vector3D(3,1,0), 0.3);
	w.addStraightSection(Vector3D(0,0,0), Vector3D(3,0,0), 0.6);
	w.print(cout);

	w.show();

	return a.exec();
}
