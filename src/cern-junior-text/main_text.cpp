#include <vector>
#include <cmath>

#include "../textview/acceleratorwidgetconsole.h"

#include "../accelerator/accelerator_cli.h"

int main(void){
	AcceleratorWidgetConsole w(Vector3D(3,2,0));

	cernjunior::build_default_accelerator(w);

	cli::add_beams(w);
	w.initialize();

	double dt(cli::getInput<double>("Timestep: (recommended: 1e-11)\ndt = "));
	if(dt <= 0) dt = simcst::DEFAULT_TIMESTEP;

	int iterations(cli::getInput<int>("Number of iterations: (-1 to continue until accelerator is empty)\n"));

	int i(0);

	try{
		while(i != iterations){
			w.evolve(dt);
			w.draw();
			if(w.is_empty()) break;
			++i;
		}

		if(i == iterations){
			std::cout << "Maximum number of iterations (" << iterations << ") was reached\n";
		}else{
			std::cout << "Accelerator is empty after " << i << " iterations\n";
		}
	}

	catch(...){
		return 1;
	}

	return 0;
}
