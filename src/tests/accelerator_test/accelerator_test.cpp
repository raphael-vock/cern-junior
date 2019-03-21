#include <iostream>

#include "../../physics/particle.h"
#include "../../accelerator/accelerator.h"

using namespace std;
using namespace basicvector;
using namespace phcst;

int main(){
	Particle p1(3.00984, -0.391837, 0, -210200, -2.64754e+08, 0, GeV/(C*C) * 0.938272, 1.60217653e-19);
	Particle p2(2.99016, -0.391837, 0, 210200, -2.64754e+08, 0, GeV/(C*C) * 0.938272, 1.60217653e-19);

	Quadrupole D(ZERO_VECTOR, X_VECTOR, 1.0, 2.0, nullptr, 1.0);
	Accelerator A({&D}, {&p1,&p2});
	cout << A << endl;
	return 0;
}
