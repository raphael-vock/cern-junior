#include "vectorfield.h"

Vector3D VectorField::operator()(const Vector3D &x) const{
	return F(x,*clock);
}

std::ostream& VectorField::print(std::ostream &stream) const{
	stream << "A vector field";
	return stream;
}

Vector3D VectorField::tangent_neighbor(const Vector3D &x) const{
	return x + simcst::FIELD_LINE_SEGMENT_LENGTH*(F(x,(clock ? *clock : 0.0)).unitary());
}

void VectorField::evolve(double dt){
	field_lines.clear();
	double t_0(clock ? *clock : 0.0);
	for(Vector3D P : sample_points){
		for(int i(0); i <= simcst::FIELD_LINE_LENGTH / simcst::FIELD_LINE_SEGMENT_LENGTH; ++i){
			try{
				Vector3D P_h(tangent_neighbor(P));
				field_lines.push_back(Arrow(canvas, P, P_h, color.modulate(F(P,t_0).norm(),F_max)));
				P = P_h;
			}catch(std::invalid_argument){ // field vanishes
				if(field_lines.empty()) break;
				P += field_lines.back().direction();
			}
		}
	}
}
