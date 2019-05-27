#include <QMainWindow>
#include <QInputDialog> // for dialog boxes
#include <QApplication>
#include <vector>
#include <cmath>

using namespace std;

#include "acceleratorwidgetgl.h"

#include "../accelerator/accelerator_cli.h"

int main(int argc, char* argv[]){
	QApplication a(argc, argv);

	AcceleratorWidgetGL w(nullptr, Vector3D(3,2,0));

	cernjunior::build_default_accelerator(w);

	cli::add_beams(w);

	w.initialize();
	w.show();

	return a.exec();
}
