#include <QMainWindow>
#include <QInputDialog> // for dialog boxes
#include <QApplication>
#include <vector>
#include <cmath>

using namespace std;

#include "acceleratorwidgetgl.h"

// Some functions for parsing console input:
string tolower(string str){
	for(char &c : str) c = tolower(c);
	return str;
}

void clear_cin(void){
	if(not cin.fail()) return;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	cout << "Come again?\n ";
}

template <typename T>
T getInput(string message){
	cout << message;
	T input;
	do{
		clear_cin();
		cin >> input;
	}while(cin.fail());
	return input;
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

	while(true){
		if(tolower(getInput<string>("Add a beam? (y/n)\n ") == "n")){
			break;
		}

		/* cout << "Type of particle? [p]roton / [e]lectron:\n "; */
		string type(tolower(getInput<string>("Type of particle? [p]roton / [e]lectron:\n ")));
		int N(getInput<int>("Enter number of particles:\n N = "));
		double E(getInput<double>("Enter median energy: (GeV) (recommended: 2.0)\n E = "));
		double lambda(getInput<double>("Enter macroparticle scaling factor\n λ = "));

		if(type == "p" or type == "proton"){
			w.addCircularBeam(Proton(Vector3D(), E, Vector3D(1,0,0)), N, lambda);
		}else if(type == "e" or type == "electron"){
			w.addCircularBeam(Electron(Vector3D(), E, Vector3D(1,0,0)), N, lambda);
		}else{
			cout << "Unrecognized particle type '" + type + "'\n";
		}
	}

	w.initialize();

	w.show();

	return a.exec();
}
