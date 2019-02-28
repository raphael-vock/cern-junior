#ifndef CONTENU_H
#define CONTENU_H

#include "drawable.h"
#include "canvas.h"

class Content : public Drawable{
	public:
		Content(Canvas* vue) : Drawable(vue), angle(0.0){}// alpha is an angle-type parameter that evolves with time
		virtual ~Content(){}

		virtual void draw() override{
			canvas->draw(*this);
		}

		void evolve(double dt);

		double getAngle(void) const { return angle; }
	private:
		double angle;
};

#endif // CONTENU_H
