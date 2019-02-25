#ifndef CANVAS_H
#define CANVAS_H
#define SUPPORT_A_DESSIN_H

class Content;

class Canvas{
	public:
		virtual ~Canvas(){}

		virtual void draw(Content const& to_draw) = 0;
};

#endif
