#pragma once

class Canvas;

class Drawable{
	public:
		Drawable(Canvas* canvas) : canvas(canvas){}
		virtual ~Drawable(){}
		virtual void draw() = 0;

	protected:
		Canvas* canvas;
};
