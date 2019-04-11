#pragma once

#include <iostream>
#include "../vector3d/vector3d.h"
#include "particle.h"

#include "../general/drawable.h"

class Box : public Drawable{
	private:
		const Vector3D center;

		const Vector3D width;
		const Vector3D depth;
		const Vector3D height;

		const double volume;

		Box(Canvas* canvas, const Vector3D &my_center, const Vector3D &my_width, const Vector3D &my_depth, const Vector3D &my_height) :
			Drawable(canvas),
			center(my_center),
			width(my_width),
			depth(my_depth),
			height(my_height),
			volume(8.0*width.norm()*depth.norm()*height.norm())
		{}

	public:
		Box(Canvas* canvas, const Vector3D &my_center, const Vector3D &my_width, double length) :
			Drawable(canvas),
			center(my_center),
			width(my_width),
			depth(length*my_width.orthogonal()),
			height(length*(width^depth).unitary()),
			volume(8.0*width.norm()*depth.norm()*height.norm())
		{}

		std::array<Vector3D,8> getVertices(void) const;

		double getVolume(void) const{ return volume; };

		bool contains(const Particle &x) const;
		std::ostream& print(std::ostream& output) const;
		Box octant(bool right, bool back, bool top) const;

		virtual void draw(void) override{ canvas->draw(*this); }
};
