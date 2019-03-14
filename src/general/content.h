#ifndef CONTENT_H
#define CONTENT_H

#include "drawable.h"
#include "canvas.h"
#include "universe.h"

class Content : public Drawable{
	private:
		Universe &omega;
	public:
		Content(Canvas* vue, Universe& my_universe) : Drawable(vue), omega(my_universe){}

		virtual ~Content(){}

		virtual void draw() override{
			canvas->draw(*this);
		}

		void evolve(double dt);

		void setUniverse(Universe omega);
		Universe* getUniverse(void) const;
};

#endif
