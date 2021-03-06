#include <iostream>

#include "../../physics/particle.h"
#include "../../misc/constants.h"

using namespace std;
using namespace phcst;

int main(void){
	const double dt(1e-11);

	/* Particle p1(Vector3D(3.00984, -0.391837), 2.0, Vector3D(-210200, -2.64754e+08), 0.938272, 1.0); */
	/* Particle p2(Vector3D(2.99016, -0.391837, 0), 2.0, Vector3D(210200, -2.64754e+08), 0.938272, 1.0); */
	Proton p1(Vector3D(3.00984, -0.391837), 2.0, Vector3D(-210200, -2.64754e+08));
	Proton p2(Vector3D(3.00984, -0.391837), 2.0, Vector3D(-210200, -2.64754e+08));

	cout << "Particle 1:\n";
	cout << p1;
	cout << "\nParticle 2:\n";
	cout << p2 << "\n";

	cout << "Applying a magnetic field B = (0,0,7) T over time dt = " << dt << ".\n\n";

	Vector3D B(0,0,7);
	p1.add_magnetic_force(B, dt);
	p2.add_magnetic_force(B, dt);
	cout << "Resultant forces on particles 1 and 2:\n";
	cout << "  F_1 = " << p1.getForce();
	cout << "\n\n  F_2 = " << p2.getForce() << "\n\n";

	p1.evolve(dt);
	p2.evolve(dt);

	cout << "Updating particle data:" << endl;
	cout << "Particle 1:\n";
	cout << p1;
	cout << "\nParticle 2:\n";
	cout << p2;
	cout << endl;

	return 0;
}
