#include <iostream>
#include "text_viewer.h"

#include "../misc/constants.h"
#include "../general/canvas.h"
#include "../physics/particle.h"

using namespace std;
using namespace phcst;

int main(void){
	TextViewer screen(cout);

	Particle p1(&screen, 3.00984, -0.391837, 0, -210200, -2.64754e+08, 0, 1e9*E/(C*C) * 0.938272, 1.60217653e-19);
	Particle p2(&screen, 2.99016, -0.391837, 0, 210200, -2.64754e+08, 0, 1e9*E/(C*C) * 0.938272, 1.60217653e-19);

	cout << "Particle 1:\n";
	p1.draw();
	cout << "\nParticle 2:\n";
	p1.draw();

	return 0;
}
