#include "content.h"

void Content::evolve(double dt){
	omega.evolve(dt);
}

void Content::setUniverse(Universe my_universe){
	omega = my_universe;
}

Universe* Content::getUniverse(void) const{
	Universe* address(&omega);
	return &omega;
}
