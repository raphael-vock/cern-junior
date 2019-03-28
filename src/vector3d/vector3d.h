#pragma once

#include <array>

#include "../color/rgb.h"
#include "../general/drawable.h"
#include "../general/canvas.h"

class Vector3D{
	private:
		double x;
		double y;
		double z;
	public:
		// Constructor, getters, setters:
		Vector3D(double a = 0, double b = 0, double c = 0) : x(a), y(b), z(c){}

		double operator[](int i) const;

		std::array<double,3> getCoords(void) const; // return coords in an array

		// Algebraic operators:
		Vector3D operator-(void) const; // returns the additive inverse
		Vector3D& operator*=(const double &);
		Vector3D operator*(const double &) const; // scalar multiplication. Note that the scalar comes AFTER the vector (i.e. u*lambda). We define lambda*u as a non-member operator
		Vector3D& operator+=(const Vector3D &); // for optimization purposes
		Vector3D operator+(Vector3D v) const; // vector addition
		Vector3D& operator-=(const Vector3D &);
		Vector3D operator-(const Vector3D &v) const; // vector subtraction
		double operator|(const Vector3D &) const; // dot product
		Vector3D operator^(const Vector3D &) const; // cross product

		// Boolean operators:
		bool operator ==(const Vector3D &) const; // returns true iff argument and *this are equal up to a small vector
		bool operator !=(const Vector3D &) const;

		// Other methods/functions with scalar output:
		double norm2(void) const; // returns square of Euclidian norm
		double norm(void) const; // returns Euclidian norm
		static double distance(const Vector3D& u, const Vector3D& v);
		static double distance2(const Vector3D& u, const Vector3D& v);
		bool is_zero(void) const; // returns true if square of norm is "zero" i.e. less than a small constants
		static double mixed_prod(const Vector3D &, const Vector3D &, const Vector3D &); // returns mixed product of (u,v,w) i.e. u|(v^w);

		// Other methods/functions with vector output:
		Vector3D rotate(Vector3D, double) const; // rotates around a given axis by a given angle angle passed as arguments
		Vector3D unitary(void) const; // returns the unit vector in the same direction
		Vector3D orthogonal(void) const; // returns an unitary orthogonal vector
		static Vector3D random_unit_vector(void);
};

namespace vctr{
	// some useful vectors for general use
	const Vector3D ZERO_VECTOR(0,0,0);
	const Vector3D X_VECTOR(1,0,0);
	const Vector3D Y_VECTOR(0,1,0);
	const Vector3D Z_VECTOR(0,0,1);
}

Vector3D operator*(const double &, const Vector3D&); // scalar multiplication, with the scalar coming BEFORE
std::ostream& operator<<(std::ostream& output, Vector3D const& v); // prints to output (e.g. std::cout or std::ofstream)

class Arrow : public Drawable{
	// represents a segment of 3D space with a start point and an endpoint
	friend class OpenGLView;
	private:
		Vector3D A;
		Vector3D B;
		RGB color;
	public:
		Arrow(Canvas* c, Vector3D a = vctr::ZERO_VECTOR, Vector3D b = vctr::ZERO_VECTOR, RGB my_color = RGB::WHITE) : Drawable(c), A(a), B(b), color(my_color){}

		Vector3D director(void) const;

		std::ostream& print(std::ostream& stream) const;
		virtual void draw(void) override{ canvas->draw(*this); }
};
