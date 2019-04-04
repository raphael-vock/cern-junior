#pragma once

#include <iostream>

#include "../accelerator/accelerator.h"

class TextView : public Canvas{
	private:
		std::ostream &stream;
	public:
		TextView(std::ostream& my_stream) : Canvas(), stream(my_stream){}
		virtual ~TextView(void){}

		virtual void draw(const Segment &to_draw) override;
		virtual void draw(const Particle &to_draw) override;
		virtual void draw(const StraightSection &to_draw) override;
		virtual void draw(const Magnetic_element &to_draw) override;
		virtual void draw(const Electric_element &to_draw) override;
		virtual void draw(const Accelerator &to_draw) override;
};
