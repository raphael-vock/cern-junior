#include "vectorfield.h"

constexpr double h(1e-3);

Vector3D VectorField::operator()(const Vector3D &x) const{
	return F(x,t);
}

std::ostream& VectorField::print(std::ostream &stream) const{
	stream << "A vector field";
	return stream;
}

Vector3D VectorField::tangent_neighbor(const Vector3D &x) const{
	try{
		return x + h*(F(x,t).unitary());
	}catch(...){ throw; }
}

void VectorField::evolve(double dt){
	t += dt;

	field_lines.clear();
	for(Vector3D P : sample_points){
		for(int i(0); i <= MAX_FIELD_LINE_LENGTH / h; ++i){
			try{
				Vector3D P_h(tangent_neighbor(P));
				field_lines.push_back(Arrow(canvas, P, P_h, color));
				P = P_h;
			}catch(...){
				// field vanishes so the field line terminates
				break;
			}
		}
	}
}
