#include <QMainWindow>
#include <QInputDialog> // for dialog boxes
#include <QApplication>
#include <vector>
#include <cmath>

using namespace std;

#include "acceleratorwidgetgl.h"

#include "../misc/commandline.h"

int main(int argc, char* argv[]){
	QApplication a(argc, argv);

	AcceleratorWidgetGL w(nullptr, Vector3D(3,2,0));

	const double r(0.5);
	const double k(1.0);

	const double B(5.89158);
	const double b(1.2);

	//*******************
	w.addFodoCell(r, b, 1.0, Vector3D(3,-2));
	w.addDipole(r,k,B, Vector3D(2,-3));
	w.addFodoCell(r, b, 1.0, Vector3D(-2,-3));
	w.addDipole(r,k,B, Vector3D(-3,-2));
	w.addFodoCell(r, b, 1.0, Vector3D(-3,2));
	w.addDipole(r,k,B, Vector3D(-2,3));
	w.addFodoCell(r, b, 1.0, Vector3D(2,3));
	w.addDipole(r,k,B);
	//*******************

	if(tolower(getInput<char>("(D)efault configuration or (c)ustom?\n") == 'c')){
		do{
			char type(tolower(getInput<char>("Type of particle? (p)roton / (e)lectron:\n")));

			char distr(tolower(getInput<char>("Distribution type? (n)one / (u)niform / (g)aussian:\n")));
			std::array<double,3> distribution_parameters;
			switch(distr){
				case 'g':{
					distribution_parameters[0] = getInput<double>("Standard deviation on position? (m) (recommended: 0.1)\nσ = ");
					distribution_parameters[1] = getInput<double>("Standard deviation on velocity? (c) (recommended: 0.01)\nσ = ");
					break;
				}
				case 'n':{
					distribution_parameters = {0.0,0.0};
					break;
				}
				case 'u':{
					distribution_parameters[0] = getInput<double>("Maximum variance on position? (m) (recommended: 0.1)\nΔ = ");
					distribution_parameters[1] = getInput<double>("Maximum variance on velocity? (c) (recommended: 0.01)\nΔ = ");
					break;
				}
			}

			int N(getInput<int>("Enter number of particles:\nN = "));
			if(N < 0) N = 0;

			double E(getInput<double>("Enter median energy: (GeV) (recommended: 2.0)\nE = "));

			double lambda(getInput<double>("Enter macroparticle scaling factor\nλ = "));
			if(lambda < simcst::ZERO_LAMBDA) lambda = 1.0;

			switch(distr){
				case 'g':
				case 'n':{
					w.addGaussianCircularBeam(*concrete_particle(Vector3D(), E, Vector3D(1,0,0), type), N, lambda, distribution_parameters[0], distribution_parameters[1]);
					break;
				}case 'u':{
					w.addUniformCircularBeam(*concrete_particle(Vector3D(), E, Vector3D(1,0,0), type), N, lambda, distribution_parameters[0], distribution_parameters[1]);
					break;
				}default:{
					cout << string("Unrecognized particle type '") + type + "'\n";
					continue;
				}
			}
		}while(tolower(getInput<char>("Add another beam? (y/n)\n") == 'y'));
	}else{ // default configuration
		w.addGaussianCircularBeam(Proton(Vector3D(), 2, Vector3D(1,0,0)), 1000, 2.0, 0.1, 0.01);
	}

	w.initialize();
	w.show();

	return a.exec();
}
