#include <iostream>
#include <initializer_list>

#include "../../accelerator/accelerator.h"

using namespace std;
using namespace phcst;

int main(){
	Accelerator A(nullptr);

	A.addParticle(Vector3D(3.00984, -0.391837, 0), Vector3D(-210200, -2.64754e+08, 0), E*1e9/(C*C) * 0.938272, 1.60217653e-19, 1e-2);
	A.addParticle(Vector3D(2.99016, -0.391837, 0), Vector3D(210200, -2.64754e+08, 0), E*1e9/(C*C) * 0.938272, 1.60217653e-19, 1e-2);

	A.addDipole(Vector3D(0,0,0), Vector3D(1,0,0), 0.5, 0.1, 2.0);
	A.addDipole(Vector3D(0,0,0), Vector3D(1,0,0), 0.5, 0.01, 2.0);
	A.addDipole(Vector3D(0,0,0), Vector3D(1,0,0), 0.5, -0.1, 2.0);
	A.addDipole(Vector3D(0,0,0), Vector3D(1,0,0), 0.5, 10, 2.0);
	A.addDipole(Vector3D(0,0,0), Vector3D(1,0,0), 0.5, -10, 2.0);

	A.print(cout);
	return 0;
}
