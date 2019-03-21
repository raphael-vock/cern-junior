#include <iostream>
#include <initializer_list>
#include <random>
#include <cmath>

#include "vector3d.h"

const int DIV_BY_ZERO(0);

void Vector3D::swap(Vector3D &u, Vector3D &v){
	std::swap(u.x,v.x);
	std::swap(u.y,v.y);
	std::swap(u.z,v.z);
}

double Vector3D::operator[](int i) const{
	switch(i){
		case 0: return x;
		case 1: return y;
		case 2: return z;
	}
	throw 2;
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
	return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vector3D Vector3D::operator^(const Vector3D &v) const{
	// note that member function binary operator overloading passes *this as first argument and the method argument as second. i.e. x^y = x.operator^(y);
	return Vector3D(
		this->y * v.z - this->z * v.y,
		v.x * this->z - v.z * this->x,
		this->x * v.y - this->y * v.x
	); 
}

double Vector3D::norm2(void) const{
	return (*this)|(*this);
}

double Vector3D::norm(void) const{
	return sqrt(norm2());
}

double Vector3D::distance(const Vector3D& u, const Vector3D& v){
	return (u - v).norm2();
}

double Vector3D::distance2(const Vector3D& u, const Vector3D& v){
	return (u - v).norm();
}

bool Vector3D::is_zero(void) const{
	return this->norm2() <= EPSILON;
}

bool Vector3D::operator==(const Vector3D& v) const{
	return (*this - v).is_zero();
}

bool Vector3D::operator!=(const Vector3D& v) const{
	return not (*this == v);
}

Vector3D Vector3D::unitary(void) const{
	if(this->is_zero()) throw DIV_BY_ZERO;
	else return (*this) * (1/this->norm());
}

Vector3D Vector3D::rotate(Vector3D u, double alpha) const{
	// rotates *this around u by an angle alpha
	// if u is zero-vector an exception will be thrown
	try{
		u = u.unitary(); // normalize
		return (cos(alpha)*(*this))
	 		    + (1.0-cos(alpha))*((*this)|u)*u +
			    + sin(alpha)*(u ^ (*this));
	}
	catch(...){ throw; }
}

Vector3D random_unit_vector(void){
	std::uniform_real_distribution<double> dis(0.0, M_PI);
	std::random_device gen;

	double phi(dis(gen));
	double theta(2 * dis(gen));
	return Vector3D(
		sin(theta) * cos(phi),
		sin(theta) * sin(phi),
		cos(theta)
	);
}

Vector3D operator*(const double &lambda, const Vector3D& u){
	return u * lambda;
}

double Vector3D::mixed_prod(const Vector3D &u, const Vector3D &v, const Vector3D &w){
	return u|(v^w);
}

std::ostream& operator<<(std::ostream& output, Vector3D const& v){
	output << v[0] << "  " << v[1] << "  " << v[2];
	return output;
}

const Vector3D Vector3D::ZERO_VECTOR(0.0,0.0,0.0);
const Vector3D Vector3D::X_VECTOR(1.0, 0.0, 0.0);
const Vector3D Vector3D::Y_VECTOR(0.0, 1.0, 0.0);
const Vector3D Vector3D::Z_VECTOR(0.0, 0.0, 1.0);
