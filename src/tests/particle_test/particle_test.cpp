#include "particle.h"
#include <ctime>
#include <fstream>

int main(){
	/* std::ofstream output; */
	/* output.open("test_particles.txt", std::ios::out|std::ios::app); */

	std::ostream output(std::cout);// la console suffit pour l'instant, pas envie de polluer le ~/ 
	auto start = std::chrono::system_clock::now();
	output << start << std::endl;
		

	// Tout ça est à revoir:
	output << "Creation of two particles : " << std::endl
	<< "One particle : " << std::endl; 
	Particle p1(3.00984, -0.391837, 0, -210200, -2.64754e+08, 0, 1.60217653e-19); 
	output << p1 << std::endl << std::endl
	<< "One particle : " << std::endl;
	Particle p2(2.99016, -0.391837, 0, 210200, -2.64754e+08, 0, 1.60217653e-19);
	output << p2 << std::endl << std::endl;

	/* output.close(); */
}
