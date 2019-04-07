#include <iostream>
#include <initializer_list>

#include "../../textview/consolewidget.h"

using namespace std;
using namespace phcst;

int main(){
	ConsoleWidget w(Vector3D(3,2,0)); 

	const double r(0.1);
	const double k(1.0);

	const double B(5.89158);
	const double b(1.2);

	const double dt(1e-11);

	// *********************
	w.addQuadrupole(r,b,Vector3D(3,1));
	w.addStraightSection(r,Vector3D(3,0));
	w.addQuadrupole(r,-b,Vector3D(3,-1));
	w.addStraightSection(r,Vector3D(3,-2));

	w.addDipole(r,k,B, Vector3D(2,-3));

	w.addQuadrupole(r,b,Vector3D(1,-3));
	w.addStraightSection(r,Vector3D(0,-3));
	w.addQuadrupole(r,-b,Vector3D(-1,-3));
	w.addStraightSection(r,Vector3D(-2,-3));

	w.addDipole(r,k,B, Vector3D(-3,-2));

	w.addQuadrupole(r,b,Vector3D(-3,-1));
	w.addStraightSection(r,Vector3D(-3,0));
	w.addQuadrupole(r,-b,Vector3D(-3,1));
	w.addStraightSection(r,Vector3D(-3,2));

	w.addDipole(r,k,B, Vector3D(-2,3));

	w.addQuadrupole(r,b,Vector3D(-1,3));
	w.addStraightSection(r,Vector3D(0,3));
	w.addQuadrupole(r,-b,Vector3D(1,3));
	w.addStraightSection(r,Vector3D(2,3));

	w.addDipole(r,k,B);

	// *********************

	w.show();

	return 0;
}
