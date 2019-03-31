#pragma once

namespace phcst{ // physical constants
	// the following are given in SI units
	constexpr double G(6.674e-11); // universal gratational constant
	constexpr double C(2.998e8); // speed of light in a vacuum
	constexpr double E(1.60218e-19); // electric charge of an electron
}

namespace simcst{ // simulation constants
	constexpr double ZERO_TIME(1e-30);
	constexpr double ZERO_DISTANCE(1e-10);
	constexpr double ZERO_VECTOR_NORM2(1e-50);

	constexpr double DEFAULT_MASS(1.0);
	constexpr double DEFAULT_RADIUS(1.0);
	constexpr double DEFAULT_CHARGE(1.0);

	constexpr double BARNES_HUT_THETA(0.5);

	constexpr double GRAVITY_SMOOTHING_EPSILON(1e-1);

	constexpr double COLLISION_ETA = 0.8;

	constexpr double FIELD_LINE_SEGMENT_LENGTH(1e-1);
	constexpr double FIELD_LINE_LENGTH(10);
	constexpr double FIELD_LINE_SAMPLE_POINT_DENSITY(0.8);

	constexpr int TORUS_NUM_QUADS(100);
	constexpr int TORUS_NUM_CYLINDERS(100);

	constexpr int CYLINDER_NUM_SIDES(20);
	constexpr double CYLINDER_SPIRAL_RATIO(0.15); // 0.0 gives no spiral. 0.25 gives a strong spiral effect
}
