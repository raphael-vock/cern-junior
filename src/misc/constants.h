#pragma once

namespace phcst{ // physical constants
	// the following are given in SI units
	constexpr double G(6.674e-11); // universal gratational constant
	constexpr double C(2.998e8); // speed of light in a vacuum
	constexpr double E(1.60218e-19); // electric charge of an electron
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

	constexpr double GRAVITY_SMOOTHING_EPSILON(1e-1);

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
}
