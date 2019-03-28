#include "vectorfield.h"

constexpr double h(1e-3);

Vector3D VectorField::operator()(const Vector3D &x) const{
	return F(x,*clock);
}

std::ostream& VectorField::print(std::ostream &stream) const{
	stream << "A vector field";
	return stream;
}

Vector3D VectorField::tangent_neighbor(const Vector3D &x) const{
	return x + h*(F(x,(clock ? *clock : 0.0)).unitary());
}

void VectorField::evolve(double dt){
	field_lines.clear();
	double t_0(clock ? *clock : 0.0);
	for(Vector3D P : sample_points){
		for(int i(0); i <= MAX_FIELD_LINE_LENGTH / h; ++i){
			try{
				Vector3D P_h(tangent_neighbor(P));
				field_lines.push_back(Arrow(canvas, P, P_h, color.modulate(F(P,t_0).norm(),F_max)));
				P = P_h;
			}catch(...){
				if(field_lines.empty()) break;
				P += field_lines.back().director();
			}
		}
	}
}
