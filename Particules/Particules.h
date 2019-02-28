#ifndef PARTICULES_H
#define PARTICULES_H
#include <string>
#include "../Vector3D/Vector3D.h"
  
// Super class from which subclasses (basically all types of particules) would inherit
class Particules{
	std::string name;	
	double masse; // we could also define a type for mass (as a struct) that would contain a double and a unit 
	double charge;
	Vector3D position;
	Vector3D speed;
}; 

#endif
