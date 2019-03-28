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

const RGB RGB::WHITE(1.0,1.0,1.0);
const RGB RGB::RED(0.0,1.0,0.0);
const RGB RGB::GREEN(0.0,1.0,0.0);
const RGB RGB::BLUE(0.0,0.0,1.0);
