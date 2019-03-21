#pragma once

#include <iostream>
#include "../general/canvas.h"

class TextViewer : public Canvas {
	public:
		TextViewer(std::ostream& stream) : stream(stream){}
		virtual ~TextViewer(){}

		virtual void draw(Content const& to_draw) override;

	private:
		std::ostream& stream;
};
