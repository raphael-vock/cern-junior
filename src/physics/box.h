#pragma once

#include <iostream>
#include "../vector3d/vector3d.h"
#include "particle.h"

class Box{
	private:
		Vector3D origin;
		double width;
		double depth;
		double height;
	public:
		Box(Vector3D my_origin, double my_width, double my_depth, double my_height) : origin(my_origin), width(my_width), depth(my_depth), height(my_height){}

		Box(double x, double y, double z, double my_width, double my_depth, double my_height) : origin(Vector3D(x,y,z)), width(my_width), depth(my_depth), height(my_height){}

		double volume(void) const;

		bool contains(const Particle &x) const;
		void print(void) const;
		Box octant(bool right, bool back, bool top) const;
};
