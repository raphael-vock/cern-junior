#include "content.h"

void Content::evolve(double dt){
	constexpr omega(100);
	angle += omega*dt;
}
