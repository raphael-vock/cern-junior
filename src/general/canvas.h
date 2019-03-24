#pragma once

#include "drawable.h"

class VectorField;
class Particle;
class StraightSection;
class Dipole;
class Quadrupole;
class Accelerator;

class Canvas{
	public:
		virtual ~Canvas(){}

		virtual void draw(const VectorField &) = 0;
		virtual void draw(const Particle &) = 0;
		virtual void draw(const Dipole &) = 0;
		virtual void draw(const Quadrupole &) = 0;
		virtual void draw(const StraightSection &) = 0;
		virtual void draw(const Accelerator &) = 0;
};
