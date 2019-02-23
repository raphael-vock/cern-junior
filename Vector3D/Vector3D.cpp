#include <iostream>
#include <cmath>
#include <string>
#include "Vector3D.h"

const double default_epsilon(1e-10);

Vector3D::Vector3D(double a, double b, double c){// by default, new vectors are 0
	x = a;
	y = b;
	z = c;
}

void Vector3D::setCoords(double a, double b, double c){
	x = a;
	y = b;
	z = c;
}

std::array<double,3> Vector3D::getCoords() const{
	std::array<double,3> coords = {x,y,z};
	return coords;
}


void Vector3D::print(void) const{
	std::cout << x << "  " << y << "  " << z << "  ";
}


Vector3D Vector3D::operator-(void) const{
	Vector3D Res;
	Res.setCoords(-x,-y,-z);
	return Res;
}

void Vector3D::operator*=(const double &lambda){
	x *= lambda;
	y *= lambda;
	z *= lambda;
}

Vector3D Vector3D::operator*(const double &lambda) const{
	Vector3D Res(*this);
	Res *= lambda;
	return Res;
}

void Vector3D::operator+=(const Vector3D &v){
	x += v.x;
	y += v.y;
	z += v.z;
}

Vector3D Vector3D::operator+(const Vector3D &v) const{
	Vector3D Res(v);
	Res += *this;
	return Res;
}

void Vector3D::operator-=(const Vector3D &v){
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

Vector3D Vector3D::operator-(const Vector3D &v) const{
	return *this + (-v);
}

double Vector3D::operator|(const Vector3D &v) const{
	return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vector3D Vector3D::operator^(const Vector3D &v) const{
	// note that member function binary operator overloading passes "this" as first argument and the method argument as second. i.e. x^y = x.operator^(y);
	Vector3D Res;
	Res.x = this->y * v.z - this->z * v.y;
	Res.y = v.x * this->z - v.z * this->x;
	Res.z = this->x * v.y - this->y * v.x;

	return Res;
}

double Vector3D::norm2(void) const{
	return (*this)|(*this);
}

double Vector3D::norm(void) const{
	return sqrt(norm2());
}

bool Vector3D::is_zero(void) const{
	return this->norm2() <= default_epsilon;
}

bool Vector3D::operator==(const Vector3D& v) const{
	return (*this - v).is_zero();
}

Vector3D Vector3D::unitary(void) const{
	if(this->is_zero()) throw 0;
	else return (*this) * (1/this->norm());
}

Vector3D operator*(const double &lambda, const Vector3D& u){
	return u * lambda;
}

double mixed_prod(const Vector3D &u, const Vector3D &v, const Vector3D &w){
	return u|(v^w);
}
