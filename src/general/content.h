#pragma once

#include "drawable.h"
#include "canvas.h"

class Content : public Drawable{
	private:
		// ...
	public:
		Content(Canvas* vue) : Drawable(vue){}

		virtual ~Content(){}

		virtual void draw() override{
			canvas->draw(*this);
		}

		void evolve(double dt);
};
