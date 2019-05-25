#include "rgb.h"
#include "../misc/exceptions.h"
#include "../misc/constants.h"

double RGB::operator[](int i) const{
	switch(i){
		case 0: return R;
		case 1: return G;
		case 2: return B;
	}
	throw excptn::BAD_RGB_ACCESS;
}

RGB RGB::modulate(double arg, double arg_max) const{
	if(arg_max <= simcst::ZERO_FORCE){
		return *this;
	}

	const double p(arg/arg_max);
	std::cout << p << " ";
	return RGB(p + (1-p)*R, (1-p)*G, (1-p)*B);
}

const RGB RGB::WHITE(1,1,1);
const RGB RGB::BLACK(0,0,0);

const RGB RGB::RED(1,0,0);
const RGB RGB::GREEN(0.13,0.54,0.13);
const RGB RGB::BLUE(0,0,1);

const RGB RGB::SKY_BLUE(0.529, 0.808, 0.922);
const RGB RGB::YELLOW(1,1,0);
const RGB RGB::ELECTRIC_BLUE(0.031, 0.573, 0.816);
const RGB RGB::PURPLE(0.0313, 0.0180, 0.8156);
