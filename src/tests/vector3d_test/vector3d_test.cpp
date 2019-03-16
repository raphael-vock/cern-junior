#include <iostream>

#include "../../vector3d/vector3d.h"

using namespace std;

int main(void){
	cout << "\n";

	Vector3D u(1.0, 2.0, -0.1);
	Vector3D v(2.6, 3.5, 4.1);
	Vector3D w(3.9, 3.8, 3.7);
	
	cout << "Si :\n u = " << u;
	cout << "\n v = " << v;
	cout << "\n w = " << w;

	cout << "\nAlors :";
	cout << "\n u+v+w = " << u+v+w;
	cout << "\n u-v = " << u-v;
	cout << "\n 3.u = " << 3.0*u;
	cout << "\n u.v = " << (u|v);
	cout << "\n u^v = " << (u^v);
	cout << "\n |u|^2 = " << u.norm2();
	cout << "\n |u| = " << u.norm();
	cout << "\n |v|^2 = " << v.norm2();
	cout << "\n |v| = " << v.norm();
	cout << "\n unitaire(v) = " << v.unitary();
	cout << "\n u.(v^w) = " << Vector3D::mixed_prod(u,v,w);

	cout << "\n\n";
}
