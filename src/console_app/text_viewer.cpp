#include <iostream> // for endl
#include "text_viewer.h"
#include "content.h"

void TextViewer::draw(Content const& to_draw){
	/* Dans ce premier exemple très simple, on n'utilise       *
	 * pas l'argument Contenu. Nous ne l'avons donc pas nommé. */

	stream << to_draw.getAngle() << std::endl;
}
