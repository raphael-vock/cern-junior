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
	w.addStraightSection(ZERO_VECTOR,Vector3D(1,0,0), 0.1);
	w.addStraightSection(Vector3D(1,0,0),Vector3D(1,1,0), 0.1);
	w.print(cout);

	w.show();

	return a.exec();
}
