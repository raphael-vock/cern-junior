#include <QMainWindow>
#include <QInputDialog> // for dialog boxes
#include <QApplication>
#include <vector>
#include <cmath>

using namespace std;

#include "acceleratorwidgetgl.h"

string make_lowercase(string &str){ // for parsing input
	for(char &c : str) c = tolower(c);
}

int main(int argc, char* argv[]){
	// get paramters of beams at runtime:

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

	/* w.addCircularBeam(Proton(Vector3D(3,1.5), 2.0, Vector3D(1,1)), 1e3, 1.0); */
	while(true){
		cout << "Enter beam? (y/n)\n";
		string answer;
		cin >> answer;
		make_lowercase(answer);

		if(answer == "y" or answer == "yes"){
			cout << "Type of particle? (E = Electron; P = Proton): ";
			char type;
			cin >> type;
			type = tolower(type);

			cout << "Enter number of particles:\n N = ";
			int n;
			cin >> n;

			cout << "Enter median energy: (GeV)\n E = ";
			int E;
			cin >> E;

			cout << "Enter macroparticle scaling factor\n λ = ";
			double lambda;
			cin >> lambda;

			switch(type){
				case 'e':{
					w.addCircularBeam(Electron(Vector3D(), E, Vector3D()), n, lambda);
					break;
				}
				case 'p':{
					w.addCircularBeam(Proton(Vector3D(), E, Vector3D()), n, lambda);
					break;
				}
				default:{
					cout << "Unrecognized particle type '".append(type) + "'\n";
				}
			}
		}else{
			break;
		}
	}

	w.initialize();

	w.show();

	return a.exec();
}
