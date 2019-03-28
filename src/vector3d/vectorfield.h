#pragma once

#include <functional>
#include <array>
#include <vector>

#include "../color/rgb.h"
#include "../general/drawable.h"
#include "../general/canvas.h"

#include "vector3d.h"
#include "../misc/constants.h"

typedef std::function<Vector3D(const Vector3D &, double t)> vector_map;

class VectorField : public Drawable{
	friend class OpenGLView;
	private:
		vector_map F;
		std::vector<Vector3D> sample_points;
		double* clock;
		RGB color;

		std::vector<Arrow> field_lines;
		double F_max; // for drawing the field lines with a gradient depending on the field's strength

	public:
		VectorField(Canvas* display = nullptr, vector_map f = [](Vector3D, double){ return vctr::ZERO_VECTOR; }, std::vector<Vector3D> my_points = {}, double* my_clock = nullptr, RGB my_color = RGB::WHITE, double my_F_max = 1.0) :
			Drawable(display),
			F(f),
			sample_points(my_points),
			clock(my_clock),
			color(my_color),
			F_max(my_F_max)
			{ evolve(); }

		// overload of call operator
		Vector3D operator()(const Vector3D &x) const;
		
		std::ostream& print(std::ostream &stream) const;
		virtual void draw(void) override{ canvas->draw(*this); }

		void setClock(double* my_clock){ clock = my_clock; }

		Vector3D tangent_neighbor(const Vector3D &x) const; // returns the tangent vector to the field at point x
		virtual void evolve(double dt = 0.0) override; // calculates field lines as a set of line segments (Arrow class) and puts them in field_lines
};
