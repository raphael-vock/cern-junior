#pragma once

#include <functional>
#include <array>
#include <vector>

#include "../misc/color.h"
#include "../general/drawable.h"
#include "../general/canvas.h"
#include "vector3d.h"

typedef std::function<Vector3D(const Vector3D &)> vector_map;

class VectorField : public Drawable{
	private:
		vector_map F;
		std::vector<Vector3D> sample_points;
		RGB color;

		static constexpr double MAX_FIELD_LINE_LENGTH = 1e1;
	public:
		VectorField(Canvas* display = nullptr, vector_map f = [](Vector3D){ return basicvector::ZERO_VECTOR; }, std::vector<Vector3D> my_points = {}, RGB my_color = {1.0,1.0,1.0}) :
			Drawable(display),
			F(f),
			sample_points(my_points),
			color(my_color)
			{}

		// overload of call operator
		Vector3D operator()(const Vector3D &x) const;
		
		std::ostream& print(std::ostream &stream) const;

		Vector3D tangent_neighbor(const Vector3D &x) const; // returns the tangent vector to the field at point x
		std::vector<Arrow> field_lines(void) const; // returns a list of line segments that approximate the field lines
};

class StaticVectorField : public VectorField{
	friend class OpenGLView;
	private:
		std::vector<Arrow> static_field_lines;	
	public:
		StaticVectorField(Canvas* display = nullptr, vector_map f = [](Vector3D){ return basicvector::ZERO_VECTOR; }, std::vector<Vector3D> my_points = {}, RGB my_color = {1.0,1.0,1.0}) :
			VectorField(display, f, my_points, my_color), static_field_lines(field_lines())
			{}

		virtual void draw(void) override{ canvas->draw(*this); }
};

class DynamicVectorField : public VectorField{
	friend class OpenGLView;
	public:
		using VectorField::VectorField; // import parents class's constructor

		virtual void draw(void) override{ canvas->draw(*this); }
};
