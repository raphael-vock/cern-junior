#include <iostream>
#include <random>
#include <cmath>

#include "vector3d.h"
#include "../misc/exceptions.h"
#include "../misc/constants.h"

double Vector3D::operator[](int i) const{
	switch(i){
		case 0: return x;
		case 1: return y;
		case 2: return z;
	}
	throw excptn::BAD_VECTOR3D_ACCESS;
}

std::array<double,3> Vector3D::getCoords() const{
	return {x,y,z};
}

Vector3D Vector3D::operator-(void) const{
	return Vector3D(-x, -y, -z);
}

Vector3D& Vector3D::operator*=(const double &lambda){
	x *= lambda;
	y *= lambda;
	z *= lambda;
	return *this;
}

Vector3D Vector3D::operator*(const double &lambda) const{
	Vector3D Res(*this);
	Res *= lambda;
	return Res;
}

Vector3D& Vector3D::operator+=(const Vector3D &v){
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3D Vector3D::operator+(Vector3D v) const{
	v += *this;
	return v;
}

Vector3D& Vector3D::operator-=(const Vector3D &v){
	return (*this += (-v));
}

Vector3D Vector3D::operator-(const Vector3D &v) const{
	return *this + (-v);
}

double Vector3D::operator|(const Vector3D &v) const{
	return x*v.x + y*v.y + z*v.z;
}

Vector3D Vector3D::operator^(const Vector3D &v) const{
	// note that member function binary operator overloading passes *this as first argument and the method argument as second. i.e. x^y = x.operator^(y);
	return Vector3D(
		y*v.z - z*v.y,
		v.x*z - v.z*x,
		x*v.y - y*v.x
	); 
}

double Vector3D::norm2(void) const{
	return (*this)|(*this);
}

double Vector3D::norm(void) const{
	return sqrt(norm2());
}

double Vector3D::distance2(const Vector3D& u, const Vector3D& v){
	return (u - v).norm2();
}

double Vector3D::distance(const Vector3D& u, const Vector3D& v){
	return (u - v).norm();
}

bool Vector3D::is_zero(void) const{
	// calculation is optimized because this method will be called very very frequently!
	if(x*x >= simcst::ZERO_VECTOR_NORM2) return false;
	if(y*y >= simcst::ZERO_VECTOR_NORM2) return false;
	if(z*z >= simcst::ZERO_VECTOR_NORM2) return false;
	return true;
}

bool Vector3D::operator==(const Vector3D& v) const{
	return (*this - v).is_zero();
}

bool Vector3D::operator!=(const Vector3D& v) const{
	return not (*this == v);
}

void Vector3D::normalize(void){
	if(this->is_zero()) throw excptn::ZERO_VECTOR_UNITARY;
	else (*this) *= 1.0/norm();
}

Vector3D Vector3D::unitary(void) const{
	if(this->is_zero()) throw excptn::ZERO_VECTOR_UNITARY;
	else return (1.0/norm())*(*this);
}

Vector3D Vector3D::orthogonal(void) const{
	if(x*x > simcst::ZERO_VECTOR_NORM2) return Vector3D(-y/x, 1.0, 0.0).unitary();
	if(y*y > simcst::ZERO_VECTOR_NORM2) return Vector3D(1.0, -x/y, 0.0).unitary();
	if(z*z > simcst::ZERO_VECTOR_NORM2) return Vector3D(1.0, 0.0, -x/z).unitary();
	else{
		// (is zero vector)
		return vctr::X_VECTOR;
	}
}

Vector3D Vector3D::rotated(Vector3D u, double alpha) const{
	try{ u.normalize(); }
	catch(std::invalid_argument){ return *this; } // u is a zero-vector then nothing happens
	return    (cos(alpha)*(*this))
     		  + (1.0-cos(alpha))*((*this)|u)*u
		  + sin(alpha)*(u^(*this));
}

Vector3D operator*(const double &lambda, const Vector3D& u){
	return u * lambda;
}

double Vector3D::mixed_prod(const Vector3D &u, const Vector3D &v, const Vector3D &w){
	return u|(v^w);
}

std::ostream& Vector3D::print(std::ostream& output) const{
	output << '(' << x << "  " << y << "  " << z << ')';
	return output;
}

std::ostream& operator<<(std::ostream& output, const Vector3D &v){
	return v.print(output);
}

std::ostream& Segment::print(std::ostream& stream) const{
	stream << '[' << A << ", " << B << ']';
	return stream;
}

Vector3D Segment::direction(void) const{
	return B - A;
}
