#pragma once

#include "drawable.h"

class Segment;
class Particle;
class Beam;
class Element;
class StraightSection;
class MagneticElement;
class ElectricElement;
class Accelerator;

class Canvas{
	private:
		Canvas(const Canvas &to_copy) = delete;
		Canvas& operator=(const Canvas &to_copy) = delete;
	public:
		Canvas(void){}
		virtual ~Canvas(){}

		virtual void draw(const Segment &) = 0;

		virtual void draw(const Particle &) = 0;
		virtual void draw(const Beam &) = 0;

		virtual void draw(const StraightSection &) = 0;
		virtual void draw(const MagneticElement &) = 0;
		virtual void draw(const ElectricElement &) = 0;

		virtual void draw(const Accelerator &) = 0;
};
