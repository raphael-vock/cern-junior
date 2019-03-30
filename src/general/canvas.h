#pragma once

#include "drawable.h"

class Arrow;
class Particle;
class Element;
class StraightSection;
class Magnetic_element;
class Electric_element;
class Accelerator;

class Canvas{
	public:
		virtual ~Canvas(){}

		virtual void draw(const Arrow &) = 0;
		virtual void draw(const Particle &) = 0;
		virtual void draw(const StraightSection &) = 0;
		virtual void draw(const Magnetic_element &) = 0;
		virtual void draw(const Electric_element &) = 0;
		virtual void draw(const Accelerator &) = 0;
};
