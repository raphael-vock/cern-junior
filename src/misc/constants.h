#pragma once

namespace phcst{ // physical constants
	static constexpr double G(1e-1);
	static constexpr double C(3e8);
	static constexpr double GeV(6.24e9);
}

namespace simcst{ // simulation constants
	static constexpr double ZERO_TIME(1e-10);
	static constexpr double ZERO_DISTANCE(1e-10);
	static constexpr double ZERO_VECTOR_NORM2(1e-10);

	static constexpr double BARNES_HUT_THETA(0.5);
}
