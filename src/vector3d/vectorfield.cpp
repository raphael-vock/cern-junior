#include "vectorfield.h"

constexpr double h(0.1);

Vector3D VectorField::operator()(const Vector3D &x) const{
	return F(x);
}

std::ostream& VectorField::print(std::ostream &stream) const{
	stream << "A vector field";
	return stream;
}

Vector3D VectorField::tangent_neighbor(const Vector3D &x) const{
	try{
		return x + h*(F(x).unitary());
	}catch(...){ throw; }
}

std::vector<Arrow> VectorField::field_lines(void) const{
	std::vector<Arrow> list;
	for(const Vector3D &P : sample_points){
		for(int i(0); i <= MAX_FIELD_LINE_LENGTH / h; ++i){
			try{
				Vector3D P_h(tangent_neighbor(P));
				list.push_back(Arrow(canvas, P, P_h, color));
			}catch(...){
				// field vanishes so the field line terminates
				break;
			}
		}
	}
	return list;
}
