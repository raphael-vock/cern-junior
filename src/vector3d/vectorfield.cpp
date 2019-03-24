#include "vectorfield.h"

Vector3D VectorField::operator()(const Vector3D &x) const{
	return F(x);
}

std::ostream& VectorField::print(std::ostream &stream) const{
	stream << "A vector field";
	return stream;
}
