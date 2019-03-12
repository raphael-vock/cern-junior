#include "../../physics/particle.h"
#include <ctime>
#include <fstream>
#include <iostream>

void time(){
	time_t tt;
	struct tm* ti;
	time(&tt);
	ti = localtime(&tt);
	std::cout << asctime(ti);
}

int main(){
	time();
	/* std::ofstream output; */
	/* output.open("test_particles.txt", std::ios::out|std::ios::app); */

	// std::ostream output(std::cout);// la console suffit pour l'instant, pas envie de polluer le ~/ 
	// auto start = std::chrono::system_clock::now();
	// output << start << std::endl;

	std::cout << "Creation of two particles : " << std::endl
	<< "One particle : " << std::endl; 
	Particle p1(3.00984, -0.391837, 0, -210200, -2.64754e+08, 0, 1.60217653e-19); 
	std::cout << p1 << std::endl << std::endl
	<< "One particle : " << std::endl;
	Particle p2(2.99016, -0.391837, 0, 210200, -2.64754e+08, 0, 1.60217653e-19);
	std::cout << p2 << std::endl << std::endl;
	
	std::cout << "Adding a magnetic force B=0 0 7 (dt=1e-11) : " << std::endl; 
	Vector3D B(0, 0, 7);
	std::cout << "To p1 : " << std::endl;
	p1.addMagneticForce(B, 1e-11);
	std::cout << p1 << std::endl;
	std::cout << "To p2 : " << std::endl;
	p2.addMagneticForce(B, 1e-11);
	std::cout << p2 << std::endl;

	std::cout << "Particles move once : " << std::endl;
	std::cout << "One particle : " << std::endl;
	p1.evolve(1e-11);
	std::cout << p1 << std::endl;
	std::cout << "One particle : " << std::endl;
	p2.evolve(1e-11);
	std::cout << p2 << std::endl;
	/* output.close(); */
}
