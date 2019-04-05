#pragma once

namespace phcst{ // physical constants
	// the following are given in atomic units
	constexpr double ATOMIC_G(2.400530e-43); // universal gratational constant
	constexpr double ATOMIC_C(137.0); //  speed of light, given by 1/α where α is the fine structure constant (≈1/137)
	constexpr double ATOMIC_C2(ATOMIC_C*ATOMIC_C); //  speed of light, given by 1/α where α is the fine structure constant (≈1/137)

	constexpr double ATOMIC_LENGTH_TO_M(5.291772e-11);
	constexpr double ATOMIC_TO_M_S(2.187680e+6);
	constexpr double ATOMIC_ENERGY_TO_GEV(2.721138e-8);
	constexpr double ATOMIC_FORCE_TO_N(8.238725e-8);
}

namespace simcst{ // simulation constants
	constexpr double DEFAULT_DT(1e-10);

	constexpr double ZERO_TIME(1e-30);
	constexpr double ZERO_DISTANCE(1e-10);
	constexpr double ZERO_VECTOR_NORM2(1e-50);
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
