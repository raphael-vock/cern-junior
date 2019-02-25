#include <iostream> // for endl
#include "text_viewer.h"
#include "content.h"

void TextViewer::draw(Content const&){
	/* Dans ce premier exemple très simple, on n'utilise       *
	 * pas l'argument Contenu. Nous ne l'avons donc pas nommé. */

	stream << "A sphere" << std::endl;
	stream << "Another sphere" << std::endl;
	stream << "A third sphere" << std::endl;
}
