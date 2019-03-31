#include "text_viewer.h"

#include <iostream>

#include "../physics/particle.h"
#include "../accelerator/element.h"
#include "../accelerator/accelerator.h"

void TextViewer::draw(const Segment &to_draw){
	stream << "A segment";
}

void TextViewer::draw(const Particle &to_draw){
	to_draw.print(stream);
}

void TextViewer::draw(const StraightSection &to_draw){
	to_draw.print(stream);
}

void TextViewer::draw(const Magnetic_element &to_draw){
	to_draw.print(stream);
}

void TextViewer::draw(const Electric_element &to_draw){
	to_draw.print(stream);
}

void TextViewer::draw(const Accelerator &to_draw){
	// TODO
}
