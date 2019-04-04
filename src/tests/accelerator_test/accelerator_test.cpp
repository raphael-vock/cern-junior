#include <iostream>
#include <initializer_list>

#include "../../textview/consolewidget.h"

using namespace std;
using namespace phcst;

int main(){
	ConsoleWidget w(Vector3D(3,2,0)); 


	const double dt(1e-3);

	w.show();

	w.evolve(dt);
	w.draw();

	return 0;
}
