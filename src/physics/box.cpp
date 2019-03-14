#include "box.h"

double Box::volume(void) const{
	return width*depth*height;
}

bool Box::contains(Particle &x){
	std::array<double,3> point_coords(x.getPosition()->getCoords());
	std::array<double,3> origin_coords(origin.getCoords());

	double delta_x(point_coords[0] - origin_coords[0]);
	double delta_y(point_coords[1] - origin_coords[1]);
	double delta_z(point_coords[2] - origin_coords[2]);
	return 0.0 <= delta_x and delta_x <= width
	   and 0.0 <= delta_y and delta_y <= depth
	   and 0.0 <= delta_z and delta_z <= height;
}

void Box::print(void) const{
	std::cout << origin << std::endl;
	std::cout << Vector3D(width, depth, height) << std::endl;
	std::cout << "\n";
}

Box Box::octant(bool right, bool back, bool top){
	std::array<double,3> originCoords(origin.getCoords());

	if(right) originCoords[0] += width*0.5;
	if(back) originCoords[1] += height*0.5;
	if(top) originCoords[2] += height*0.5;

	return Box(originCoords[0], originCoords[1], originCoords[2], width*0.5, depth*0.5, height*0.5);
}
