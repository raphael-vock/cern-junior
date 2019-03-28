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

		static const RGB WHITE;
		static const RGB RED;
		static const RGB GREEN;
		static const RGB BLUE;
};

