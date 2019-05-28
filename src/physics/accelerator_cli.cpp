#include "accelerator_cli.h"
#include <string>

// Some functions for parsing console input:

void cli::try_again(void){
	if(not std::cin.fail()) return;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	std::cout << "Come again?\n";
}

void cli::add_beams(Accelerator &w){
	if(std::tolower(cli::getInput<char>("(D)efault configuration or (c)ustom?\n") == 'c')){
		do{
			char type(std::tolower(cli::getInput<char>("Type of particle: (p)roton / (e)lectron:\n")));

			int N(cli::getInput<int>("Number of particles:\nN = "));
			if(N < 0) N = 0;

			double E(cli::getInput<double>("Median energy: (GeV) (recommended: 2.0)\nE = "));

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

			switch(distr){
				case 'g':
				case 'n':{
					w.addGaussianCircularBeam(*concrete_particle(Vector3D(), E, Vector3D(1,0,0), type), N, lambda, distr_param, 0.0);
					break;
				}case 'u':{
					w.addUniformCircularBeam(*concrete_particle(Vector3D(), E, Vector3D(1,0,0), type), N, lambda, distr_param, 0.0);
					break;
				}default:{
					std::cout << std::string("Unrecognized particle type '") + type + "'\n";
					continue;
				}
			}
		}while(std::tolower(cli::getInput<char>("Add another beam? (y/n)\n") == 'y'));
	}else{ // default configuration
		w.addGaussianCircularBeam(Proton(Vector3D(), 2, Vector3D(1,0,0)), 1000, 2.0, 0.1, 0.01);
	}
}
