#include "text_viewer.h"

#include <iostream>

#include "../physics/particle.h"
#include "../accelerator/element.h"
#include "../accelerator/accelerator.h"

void TextViewer::draw(const Arrow &to_draw){
	stream << "An arrow";
}

void TextViewer::draw(const VectorField &to_draw){
	stream << "A vector field";
}

void TextViewer::draw(const Particle &to_draw){
	to_draw.print(stream);
}

void TextViewer::draw(const StraightSection &to_draw){
	to_draw.print(stream);
}

void TextViewer::draw(const Dipole &to_draw){
	to_draw.print(stream);
}

void TextViewer::draw(const Quadrupole &to_draw){
	to_draw.print(stream);
}

void TextViewer::draw(const RadiofrequencyCavity &to_draw){
	to_draw.print(stream);
}

void TextViewer::draw(const Accelerator &to_draw){
	/* to_draw.print(stream); */
	// provokes linker error for some reason
}
