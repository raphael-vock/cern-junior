#include <iostream>
#include "Vector3D.h"

using namespace std;

int main(void){
	cout << "\n";

	Vector3D u;
	Vector3D v;
	Vector3D w;
	u.setCoords(1.0, 2.0, -0.1);
	v.setCoords(2.6, 3.5, 4.1);
	w.setCoords(3.9, 3.8, 3.7);
	
	cout << "Si :\n u = "; u.print();
	cout << "\n v = "; v.print();
	cout << "\n w = "; w.print();

	cout << "\nAlors :";
	cout << "\n u+v+w = "; (u+v+w).print();
	cout << "\n u-v = "; (u-v).print();
	cout << "\n 3.u = "; (3.0*u).print();
	cout << "\n u.v = "; cout << (u|v);
	cout << "\n u^v = "; (u^v).print();
	cout << "\n |u|^2 = "; cout << u.norm2();
	cout << "\n |u| = "; cout << u.norm();
	cout << "\n |v|^2 = "; cout << v.norm2();
	cout << "\n |v| = "; cout << v.norm();
	cout << "\n unitaire(v) = "; v.unitary().print();
	cout << "\n u.(v^w) = "; cout << mixed_prod(u,v,w);

	cout << "\n\n";
}
