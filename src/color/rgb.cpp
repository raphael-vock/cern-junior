#include "rgb.h"
#include "../misc/exceptions.h"

double RGB::operator[](int i) const{
	switch(i){
		case 0: return R;
		case 1: return G;
		case 2: return B;
	}
	throw excptn::BAD_RGB_ACCESS;
}

RGB RGB::modulate(double arg, double arg_max) const{
	const double p(arg/arg_max);
	return RGB((1-p)*R + p, (1-p)*G + p, (1-p)*B + p);
}

const RGB RGB::WHITE(1,1,1);
const RGB RGB::BLACK(0,0,0);

const RGB RGB::RED(1,0,0);
const RGB RGB::GREEN(0,1,0);
const RGB RGB::BLUE(0,0,1);

const RGB RGB::ELECTRIC_BLUE(49.0/255, 55.0/255, 253.0/255);
const RGB RGB::SKY_BLUE(0.529, 0.808, 0.922);
const RGB RGB::YELLOW(1,1,0);
