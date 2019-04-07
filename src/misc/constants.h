#pragma once

namespace phcst{ // physical constants
	// the following are given in c.g.s. units
	constexpr double G_CGS(6.67428e-8); // universal gratational constant
	constexpr double C_CGS(2.99792458e10); // speed of light
	constexpr double C2_CGS(C_CGS * C_CGS); // speed of light squared
	constexpr double E_CGS(4.80320427e-10); // elementary charge

	constexpr double GEV_C2_CGS(1e-13*C2_CGS/E_CGS);
	constexpr double GEV_CGS(1.602176621e-3);
	constexpr double C_CHARGE_CGS(3.33564e-10);
	constexpr double T_CGS(1e4);
}

namespace simcst{ // simulation constants
	constexpr double DEFAULT_DT(1e-10);

	constexpr double ZERO_TIME(1e-30);
	constexpr double ZERO_DISTANCE(1e-10);
	constexpr double ZERO_VECTOR_NORM2(1e-50);
	constexpr double ZERO_ENERGY_GEV(1e-10);
	constexpr double ZERO_CURVATURE(1e-5);
	constexpr double ZERO_LAMBDA(1e-3);

	constexpr double DEFAULT_MASS(1.0);
	constexpr double DEFAULT_RADIUS(1.0);
	constexpr double DEFAULT_CHARGE(1.0);

	constexpr double BARNES_HUT_THETA(0.5);

	constexpr double GRAVITY_SMOOTHING_EPSILON(1.0); // NOTE: this is in atomic units (of length)

	constexpr double COLLISION_ETA = 0.8;

	constexpr double FIELD_LINE_SEGMENT_LENGTH(1e-1);
	constexpr double FIELD_LINE_LENGTH(10);
	constexpr double FIELD_LINE_SAMPLE_POINT_DENSITY(0.8);

	constexpr double CYLINDER_QUAD_LENGTH(0.05);
	constexpr double TORUS_QUAD_LENGTH(0.05);

	constexpr double CYLINDER_TUBE_HEIGHT(0.08);
	constexpr double TORUS_TUBE_HEIGHT(0.05);

	constexpr int HIGHLIGHT_COLOR_FREQUENCY(1);

	constexpr int CYLINDER_NUM_SIDES(20);

	constexpr double REPRESENTED_RADIUS_ELECTRON(0.1);
}
