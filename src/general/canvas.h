#pragma once

#include "drawable.h"

class Arrow;
class StaticVectorField;
class DynamicVectorField;
class Particle;
class Element;
class StraightSection;
class Dipole;
class Quadrupole;
class Accelerator;

class Canvas{
	public:
		virtual ~Canvas(){}

		virtual void draw(const Arrow &) = 0;
		virtual void draw(const StaticVectorField &) = 0;
		virtual void draw(const DynamicVectorField &) = 0;
		virtual void draw(const Particle &) = 0;
		virtual void draw(const Dipole &) = 0;
		virtual void draw(const Quadrupole &) = 0;
		virtual void draw(const StraightSection &) = 0;
		virtual void draw(const Accelerator &) = 0;
};
