#include "Dimension.h"

Dimension::Dimension(std::string u, double var_epsilon){
	unit = u;
	epsilon = var_epsilon;
}

void Dimension::print(void) const{
	std::cout << unit;
}

bool Dimension::operator==(const Dimension &dim_arg){
	return this->unit == dim_arg.unit;
}

Dimension* MASS(new Dimension("kg",1e-23));
Dimension* LENGTH(new Dimension("m",1e-10));
Dimension* VELOCITY(new Dimension("m/s",1e-5));
Dimension* ACCELERATION(new Dimension("m/s^2",1e-5));
Dimension* ENERGY(new Dimension("J",1e-5));
