#pragma once

#include <iostream>

#include "../general/canvas.h"
#include "../general/drawable.h"

class TextViewer : public Canvas{
	private:
		std::ostream &stream;
	public:
		TextViewer(std::ostream& my_stream) : stream(my_stream){}
		virtual ~TextViewer(){}

		virtual void draw(const Arrow &to_draw) override;
		virtual void draw(const Particle &to_draw) override;
		virtual void draw(const VectorField &to_draw) override;
		virtual void draw(const StraightSection &to_draw) override;
		virtual void draw(const Dipole &to_draw) override;
		virtual void draw(const Quadrupole &to_draw) override;
		virtual void draw(const RadiofrequencyCavity &to_draw) override;
		virtual void draw(const Accelerator &to_draw) override;
};
