#include <iostream>
#include <initializer_list>

#include "../../textview/consolewidget.h"

using namespace std;
using namespace phcst;

int main(){
	Dipole d(nullptr, Vector3D(0,0), Vector3D(2,0), 0.2, -1, nullptr, 0);
	cout << d.inverse_curvilinear_coord(0) << "\n"; 
	cout << d.inverse_curvilinear_coord(0.1) << "\n"; 
	cout << d.inverse_curvilinear_coord(0.5) << "\n"; 
	cout << d.inverse_curvilinear_coord(0.7) << "\n"; 
	cout << d.inverse_curvilinear_coord(1) << "\n"; 

	return 0;
}
