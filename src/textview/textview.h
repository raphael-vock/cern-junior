#pragma once

#include <iostream>

#include "../accelerator/accelerator.h"
#include "../physics/beam.h"

class TextView : public Canvas{
	private:
		std::ostream &stream;
	public:
		TextView(std::ostream& my_stream) : Canvas(), stream(my_stream){}
		virtual ~TextView(void){}

		virtual void draw(const Segment &to_draw) override;
		virtual void draw(const Particle &to_draw) override;
		virtual void draw(const Beam &to_draw) override;
		virtual void draw(const StraightSection &to_draw) override;
		virtual void draw(const MagneticElement &to_draw) override;
		virtual void draw(const ElectricElement &to_draw) override;
		virtual void draw(const Accelerator &to_draw) override;
};
