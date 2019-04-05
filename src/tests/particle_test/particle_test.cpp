#include <iostream>

#include "../../physics/particle.h"
#include "../../misc/constants.h"

using namespace std;
using namespace phcst;

int main(){
	const double dt(1e-11);

	Particle p1(1.0/ATOMIC_LENGTH_TO_M*Vector3D(3.00984, -0.391837, 0), 1.0/ATOMIC_TO_M_S*Vector3D(-210200, -2.64754e+08, 0), ATOMIC_C2/ATOMIC_ENERGY_TO_GEV * 0.938272, 1.0, 0.0);
	Particle p2(1.0/ATOMIC_LENGTH_TO_M*Vector3D(2.99016, -0.391837, 0), 1.0/ATOMIC_TO_M_S*Vector3D(210200, -2.64754e+08, 0), ATOMIC_C2/ATOMIC_ENERGY_TO_GEV * 0.938272, 1.0, 0.0);

	cout << "Particle 1:\n";
	cout << p1;
	cout << "\nParticle 2:\n";
	cout << p2 << "\n";

	cout << "Applying a magnetic force B = (0,0,7) over time dt = " << dt << ".\n";

	// TODO convert B to atomic units
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
