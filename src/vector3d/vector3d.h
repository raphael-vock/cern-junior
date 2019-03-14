#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <array>
#include <initializer_list>
#include <cmath>
#include <random>

class Vector3D;

const extern double EPSILON;
const extern Vector3D ZERO_VECTOR;

// the three unit vectors:
const extern Vector3D X_VECTOR;
const extern Vector3D Y_VECTOR;
const extern Vector3D Z_VECTOR;

class Vector3D{
	private:
		double x;
		double y;
		double z;
	public:
		// Constructor, getters, setters:
		Vector3D(double a = 0, double b = 0, double c = 0) : x(a), y(b), z(c){}

		// void setCoords(double a, double b, double c); // intialise instance of Vector3D to the given coords
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

		// Other methods with scalar output:
		double norm2(void) const; // returns square of Euclidian norm
		double norm(void) const; // returns Euclidian norm
		bool is_zero(void) const; // returns true if square of norm is "zero" i.e. less than EPSILON

		// Other methods with vector output:
		Vector3D rotate(Vector3D, double) const; // rotates around a given axis by a given angle angle passed as arguments
		Vector3D unitary() const; // returns the unit vector in the same direction
};

Vector3D random_unit_vector(void);

Vector3D operator*(const double &, const Vector3D&); // scalar multiplication, with the scalar coming BEFORE

double mixed_prod(const Vector3D &, const Vector3D &, const Vector3D &); // returns mixed product of (u,v,w) i.e. u|(v^w);

std::ostream& operator<<(std::ostream& output, Vector3D const& v); // prints to output (e.g. std::cout or std::ofstream)

double distance(const Vector3D& u, const Vector3D& v);
double distance2(const Vector3D& u, const Vector3D& v);

#endif
