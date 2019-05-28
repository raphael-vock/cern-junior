#include "accelerator_cli.h"
#include <string>

using namespace std;

// Some functions for parsing console input:

void cli::try_again(void){
	if(not cin.fail()) return;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	cout << "Come again?\n";
}

void cli::add_beams(Accelerator &w){
	if(std::tolower(cli::getInput<char>("(D)efault configuration or (c)ustom?\n") == 'c')){
		do{
			char type(std::tolower(cli::getInput<char>("Type of particle: (p)roton / (e)lectron:\n")));

			int N(cli::getInput<int>("Number of particles:\nN = "));
			if(N < 0) N = 0;

			char distr(std::tolower(cli::getInput<char>("Distribution type: (n)one / (u)niform / (g)aussian:\n")));

			double distr_param;
			switch(distr){
				case 'g':{
					distr_param = cli::getInput<double>("Standard deviation on position? (m) (recommended: 0.1)\nσ = ");
					break;
				}
				case 'n':{
					distr_param = 0.0;
					break;
				}
				case 'u':{
					distr_param = cli::getInput<double>("Maximum variance on position? (m) (recommended: 0.1)\nΔ = ");
					break;
				}
			}

			double lambda(cli::getInput<double>("Macroparticle scaling factor (≥ 1): (lower is more precise, bigger is more efficient)\nλ = "));
			if(lambda < 1) lambda = 1.0;

			try{
				switch(distr){
					case 'g':
					case 'n':{
						w.addGaussianCircularBeam(*concrete_particle(Vector3D(), 2.0, Vector3D(1,0,0), type), N, lambda, distr_param, 0.0);
						break;
					}case 'u':{
						w.addUniformCircularBeam(*concrete_particle(Vector3D(), 2.0, Vector3D(1,0,0), type), N, lambda, distr_param, 0.0);
						break;
					}default:{
						cout << string("Unrecognized distribution type '") + distr + "'\n";
						continue;
					}
				}
			}
			catch(...){
				cout << string("Unrecognized particle type '") + type + "'\n";
				continue;
			}
		}while(std::tolower(cli::getInput<char>("Add another beam? (y/n)\n") == 'y'));
	}else{ // default configuration
		w.addGaussianCircularBeam(Proton(Vector3D(), 2, Vector3D(1,0,0)), 1000, 2.0, 0.1, 0.01);
	}
}

void cli::print_keybindings(char lang, ostream& output){
	switch(lang){
		case 'f':{
			cout << "* Se déplacer avec W-A-S-D\n";
			cout << "* Clic gauche + souris pour changer de PDV\n";
			cout << endl;
			cout << "* Saisir '1' pour entrer dans le PDV 1ère personne\n";
			cout << "* Saisir '3' pour entrer dans le PDV 3ème personne\n";
			cout << "* Saisir '2' pour reprendre le PDV libre\n";
			cout << endl;
			cout << "* Saisir '+' pour augmenter la vitesse de la simulation\n";
			cout << "* Saisir '=' pour baisser la vitesse de la simulation\n";
			cout << endl;
			cout << "* Saisir 'M' pour entrer/sortir du mode matrice\n";
			break;
		}default:{ // English by default
			cout << "* Move with W-A-S-D\n";
			cout << "* Left-click and move mouse to change viewpoint\n";
			cout << endl;
			cout << "* Press '1' to enter 1st-person POV\n";
			cout << "* Press '3' to enter 3rd-person POV\n";
			cout << "* Press '2' to re-enter unconstrained POV\n";
			cout << endl;
			cout << "* Press '+' to increase simulation speed\n";
			cout << "* Press '=' to decrease simulation speed\n";
			cout << endl;
			cout << "* Press 'M' to toggle matrix mode\n";
			break;
		}
	}
	cout << endl;
}

void cli::offer_keybindings(void){
	char ask(std::tolower(getInput<char>("View keybindings? (y/n)\n")));

	switch(ask){
		case 'y':{
			string lang((getInput<string>("Language? (fr/en)\n")));
			print_keybindings(lang.empty() ? 'e' : std::tolower(lang[0]));
			break;
		}
		default: break;
	}
}
