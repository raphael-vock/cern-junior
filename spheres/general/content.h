#ifndef CONTENU_H
#define CONTENU_H

#include "drawable.h"
#include "canvas.h"

class Content : public Drawable{
public:
	Content(Canvas* vue) : Drawable(vue){}
	virtual ~Content(){}

	virtual void draw() override{
		canvas->draw(*this);
	}
};

#endif // CONTENU_H
