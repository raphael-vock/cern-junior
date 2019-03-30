#include <iostream>

#include "../../physics/particle.h"
#include "../../misc/constants.h"

using namespace std;
using namespace phcst;

int main(){
	const double dt(1e-11);

	Particle p1(nullptr, Vector3D(3.00984, -0.391837, 0), Vector3D(-210200, -2.64754e+08, 0), 1e9*E/(C*C) * 0.938272, 1.60217653e-19);
	Particle p2(nullptr, Vector3D(2.99016, -0.391837, 0), Vector3D(210200, -2.64754e+08, 0), 1e9*E/(C*C) * 0.938272, 1.60217653e-19);

	cout << "Particle 1:\n";
	cout << p1;
	cout << "\nParticle 2:\n";
	cout << p2 << "\n";

	cout << "Applying a magnetic force B = (0,0,7) over time dt = " << dt << ".\n";

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
