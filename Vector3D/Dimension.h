#include <string>
#include <iostream>

class Dimension{
	private:
		std::string unit;// e.g. "m", "m/s", "eV", etc.
	public:
		double epsilon;// small positive number beneath which objects of this type are considered zero

		Dimension(std::string, double);

		void print(void) const;
		bool operator==(const Dimension &);// testing if two dimensions are equal
};

extern Dimension* MASS;
extern Dimension* LENGTH;
extern Dimension* VELOCITY;
extern Dimension* ACCELERATION;
extern Dimension* ENERGY;
