#include "particle.h"
#include <ctime>
#include <fstream>

void time(){
	std::ofstream output;
	output.open("test_particles.txt", std::ios::out|std::ios::app);

	time_t tt; // argument for time
	struct tm* ti; // store time
	time(&tt); // applying time
	ti = localtime(&tt); // using local time
	for (int i(0); i <= 15; ++i){
		output << '-';
	}
	output << " "  << asctime(ti);
	output.close();
}

int main(){
	time(); // displays the date at the begining of every new test 
		
	std::ofstream output;
	output.open("test_particles.txt", std::ios::out|std::ios::app);

	output << "Creation of two particles : " << std::endl
	<< "One particle : " << std::endl; 
	Particle p1(3.00984, -0.391837, 0, -210200, -2.64754e+08, 0, 1.60217653e-19); 
	output << p1 << std::endl << std::endl
	<< "One particle : " << std::endl;
	Particle p2(2.99016, -0.391837, 0, 210200, -2.64754e+08, 0, 1.60217653e-19);
	output << p2 << std::endl << std::endl;

	output.close();
}
