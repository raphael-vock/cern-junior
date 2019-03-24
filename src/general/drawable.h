#pragma once
#include <iostream>

class Canvas;

class Drawable{
	protected:
		Canvas* canvas;
	public:
		Drawable(Canvas* my_canvas) : canvas(my_canvas){}
		virtual ~Drawable(void){}

		virtual void draw(void) = 0;
};
