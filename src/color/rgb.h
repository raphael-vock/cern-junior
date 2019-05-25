#pragma once

#include <array>

class RGB{
	private:
		double R;
		double G;
		double B;
	public:
		RGB(double r, double g, double b) : R(r), G(g), B(b){}
		double operator[](int i) const;

		RGB modulate(double arg, double arg_max) const; // modulates the color from the base color (arg == 0) to red (arg == arg_max)

		static const RGB WHITE;
		static const RGB BLACK;

		static const RGB RED;
		static const RGB GREEN;
		static const RGB BLUE;

		static const RGB YELLOW;
		static const RGB SKY_BLUE;
		static const RGB ELECTRIC_BLUE;
		static const RGB PURPLE;
};
