#include <iostream>
#include <initializer_list>

#include "../../accelerator/accelerator.h"

using namespace std;
using namespace phcst;

int main(){
	Particle p1(nullptr, 3.00984, -0.391837, 0, -210200, -2.64754e+08, 0, GeV/(C*C) * 0.938272, 1.60217653e-19);
	Particle p2(nullptr, 2.99016, -0.391837, 0, 210200, -2.64754e+08, 0, GeV/(C*C) * 0.938272, 1.60217653e-19);

	Dipole D(nullptr, vctr::ZERO_VECTOR, {1.0,0.0,0.0}, 0.5, 0.5, nullptr, 2.0);
	Quadrupole Q(nullptr, {1.0,0.0,0.0}, {2.0,0.0,0.0}, 1.0, 2.0, nullptr, 1.0);
	StraightSection S(nullptr, {2.0,0.0,0.0}, {3.0,0.0,0.0}, 1.0, nullptr);

	Accelerator A(nullptr, {&D, &Q, &S}, {&p1,&p2});
	cout << A << endl;
	return 0;
}
