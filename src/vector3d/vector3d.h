#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <array>
#include <initializer_list>
#include <cmath>
#include <random>

const extern double default_epsilon;

class Vector3D{
	private:
		double x;
		double y;
		double z;
	public:

// --------------------------------------- Constructor getters, setters ----------------------------------------------------

		Vector3D(double a = 0, double b = 0, double c = 0) : x(a), y(b), z(c){}

		void setCoords(double a, double b, double c);// intialise instance of Vector3D to the given coords
		std::array<double,3> getCoords(void) const;// return coords in an array


// ---------------------------------------- Algebric operators --------------------------------------------------------------

		Vector3D operator-(void) const;// returns the additive inverse
		Vector3D& operator*=(const double &);
		Vector3D operator*(const double &) const;// scalar multiplication. Note that the scalar comes AFTER the vector (i.e. u*lambda). We define lambda*u as a non-member operator
		Vector3D& operator+=(const Vector3D &);// for optimization purposes
		Vector3D operator+(Vector3D v) const;// vector addition
		Vector3D& operator-=(const Vector3D &);
		Vector3D operator-(const Vector3D &v) const;// vector subtraction
		double operator|(const Vector3D &) const;// dot product
		Vector3D operator^(const Vector3D &) const;// cross product

		bool operator ==(const Vector3D &) const;// returns true if argument and "this" differ by a "zero" vector
		bool operator !=(const Vector3D &) const;
		Vector3D unitary() const;// returns the unit vector in the same direction

		Vector3D rotate(Vector3D axis, double angle); // when applied to a vector x, returns the resulting vector of the rotation cos(t) x + ( 1-cos(t) ) (x*a) a + sin(t) a ^ x

// --------------------------------------- Constant methods ----------------------------------------------------------------

		double norm2(void) const;// returns square of Euclidian norm
		double norm(void) const;// returns Euclidian norm
		bool is_zero(void) const;// returns true if square of norm is less than the tolerance specified by the vector's dimension  
		void print(void) const;// print coords in console
};

Vector3D random_unit_vector(void);

Vector3D operator*(const double &, const Vector3D&);// scalar multiplication, with the scalar coming BEFORE

double mixed_prod(const Vector3D &, const Vector3D &, const Vector3D &);// returns mixed product of (u,v,w) i.e. u|(v^w);

std::ostream& operator<<(std::ostream& output, Vector3D const& v);// overloaded operator to print a vector

#endif
