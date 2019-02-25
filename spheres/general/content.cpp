#include "content.h"

void Content::evolve(double dt){
	constexpr double omega(100.0);
	angle += omega*dt;
}
