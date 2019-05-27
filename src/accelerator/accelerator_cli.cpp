#include "accelerator_cli.h"
#include <string>

// Some functions for parsing console input:

/* std::string cli::tolower(std::string str){ */
/* 	for(char &c : str) c = tolower(c); */
/* 	return str; */
/* } */

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

			double lambda(cli::getInput<double>("Macroparticle scaling factor (≥ 1): (lower is more precise, bigger is more efficient)\nλ = "));
			if(lambda < 1) lambda = 1.0;

			std::array<double,3> distribution_parameters;
			switch(distr){
				case 'g':{
					distribution_parameters[0] = cli::getInput<double>("Standard deviation on position? (m) (recommended: 0.1)\nσ = ");
					distribution_parameters[1] = cli::getInput<double>("Standard deviation on velocity? (c) (recommended: 0.01)\nσ = ");
					break;
				}
				case 'n':{
					distribution_parameters = {0.0,0.0};
					break;
				}
				case 'u':{
					distribution_parameters[0] = cli::getInput<double>("Maximum variance on position? (m) (recommended: 0.1)\nΔ = ");
					distribution_parameters[1] = cli::getInput<double>("Maximum variance on velocity? (c) (recommended: 0.01)\nΔ = ");
					break;
				}
			}

			switch(distr){
				case 'g':
				case 'n':{
						   w.addGaussianCircularBeam(*concrete_particle(Vector3D(), E, Vector3D(1,0,0), type), N, lambda, distribution_parameters[0], distribution_parameters[1]);
						   break;
					   }case 'u':{
						   w.addUniformCircularBeam(*concrete_particle(Vector3D(), E, Vector3D(1,0,0), type), N, lambda, distribution_parameters[0], distribution_parameters[1]);
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
