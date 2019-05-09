#pragma once

#include "drawable.h"

class Segment;
class Box;
class Particle;
class Beam;
/* class ScatterPlot; */
class Element;
class Accelerator;

class Canvas{
	private:
		Canvas(const Canvas &to_copy) = delete;
		Canvas& operator=(const Canvas &to_copy) = delete;
	public:
		Canvas(void){}
		virtual ~Canvas(void){}

		virtual void draw(const Segment &) = 0;
		virtual void draw(const Box &) = 0;

		virtual void draw(const Particle &) = 0;
		virtual void draw(const Beam &) = 0;
		/* virtual void draw(const ScatterPlot &) = 0; */

		virtual void draw(const Element &) = 0;

		virtual void draw(const Accelerator &) = 0;
};
