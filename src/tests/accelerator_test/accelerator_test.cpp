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

	w.addParticle(Particle(Vector3D(3.01,0), Vector3D(0, -2.64754e8), 1e9/(ATOMIC_C2) * 0.938272, 1.0, r, &RGB::BLUE));
	// *********************

	w.show();

	w.evolve(dt);
	w.draw();
	w.evolve(dt);
	w.draw();
	w.evolve(dt);
	w.draw();
	w.evolve(dt);
	w.draw();

	return 0;
}
