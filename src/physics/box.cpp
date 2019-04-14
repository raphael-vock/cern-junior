#include "box.h"

std::array<Vector3D,8> Box::getVertices(void) const{
	// TODO replace with "getVertices"
	return {
		center - width - height - depth,
		center - width - height + depth,
		center - width + height - depth,
		center - width + height + depth,

		center + width + height - depth,
		center + width + height + depth,
		center + width - height - depth,
		center + width - height + depth,
	};
}

bool Box::contains(const Particle &x) const{
	Vector3D rel_coords(x - center + width + depth + height);

	double a(0.5*rel_coords|width);
	double b(0.5*rel_coords|depth);
	double c(0.5*rel_coords|height);

	return
		0.0 <= a and a <= width.norm2() and
		0.0 <= b and b <= depth.norm2() and
		0.0 <= c and c <= height.norm2();
}

std::ostream& Box::print(std::ostream &output) const{
	output << center << "\n";
	output << width << "\n";
	output << depth << "\n";
	output << height << "\n\n";
	return output;
}

Box Box::octant(bool right, bool back, bool top) const{
	Vector3D new_center(center);

	Vector3D new_width(0.5*width);
	Vector3D new_depth(0.5*depth);
	Vector3D new_height(0.5*height);

	new_center += (right ? 1 : -1) * new_width;
	new_center += (back ? 1 : -1) * new_depth;
	new_center += (top ? 1 : -1) * new_height;

	return Box(canvas, new_center, new_width, new_depth, new_height);
}
