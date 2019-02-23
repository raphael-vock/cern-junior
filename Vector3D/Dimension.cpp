#include "Dimension.h"

Dimension::Dimension(std::string u, double epsilon){
	unit = u;
	tolerance = epsilon;
}

bool Dimension::operator==(const Dimension &dim_arg){
	return this->unit == dim_arg.unit;
}

Dimension* A(new Dimension("",1e-3));// adimensional
Dimension* MASS(new Dimension("kg",1e-23));
Dimension* LENGTH(new Dimension("m",1e-10));
Dimension* VELOCITY(new Dimension("m/s",1e-5));
Dimension* ACCELERATION(new Dimension("m/s^2",1e-5));
Dimension* ENERGY(new Dimension("J",1e-5));
