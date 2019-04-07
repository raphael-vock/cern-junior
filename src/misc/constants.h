#pragma once

namespace phcst{ // physical constants
	// the following are given in c.g.s. units
	constexpr double G_USI(6.674e-11); // universal gratational constant
	constexpr double C_USI(2.99792458e8); // speed of light
	constexpr double C2_USI(C_USI * C_USI); // speed of light squared
	constexpr double E_USI(1.602176487e-19); // elementary charge

	constexpr double MASS_PROTON_GEV_C2(0.938272);
	constexpr double MASS_ELECTRON_GEV_C2(5.10999e-4);
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

	constexpr double REPRESENTED_RADIUS_ELECTRON(0.02);
	constexpr double REPRESENTED_RADIUS_PROTON(0.02);
}
