#include <string>
#include <iostream>

class Dimension{
	private:
		std::string unit;// e.g. "m", "m/s", "eV", etc.
	public:
		double tolerance;// small positive number beneath which objects of this type are considered zero

		Dimension(std::string, double);

		void print(void){ std::cout << unit; }
		bool operator==(const Dimension &);// testing if two dimensions are equal
};

// LES VALEURS NUMERIQUES SONT A TITRE D'ILLUSTRATION. On les modifiera plus tard.

extern Dimension* A;
extern Dimension* MASS;
extern Dimension* LENGTH;
extern Dimension* VELOCITY;
extern Dimension* ACCELERATION;
extern Dimension* ENERGY;
