#include "text_viewer.h"
#include <iostream> // for endl
#include "content.h"

void TextViewer::draw(Content const& to_draw){
	stream << "There are " << to_draw.getUniverse()->getParticle_list()->size() << " particles in the universe\n";
}
