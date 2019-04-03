#pragma once

#include <iostream>

namespace excptn{
	const std::invalid_argument ZERO_VECTOR_UNITARY("Could not normalize zero-vector");
	const std::out_of_range BAD_VECTOR3D_ACCESS("Could not access Vector3D's i-th coordinates for i≠0,1,2");
	const std::out_of_range BAD_RGB_ACCESS("Could not access RGB's i-th value for i≠0,1,2");

	const std::invalid_argument ZERO_CURVATURE_CENTER("Center of circle with zero curvature is undefined");
	const std::invalid_argument ZERO_CURVATURE_DIPOLE("Dipole must have nonzero curvature");
	
	const std::invalid_argument ELEMENT_DEGENERATE_GEOMETRY("Invalid element geometric parameters");
}
