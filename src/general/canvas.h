#ifndef CANVAS_H
#define CANVAS_H

class Content;

class Canvas{
	public:
		virtual ~Canvas(){}

		virtual void draw(Content const& to_draw) = 0;
};

#endif
