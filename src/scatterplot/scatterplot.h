#pragma once

#include "../general/canvas.h"
#include <string>
#include <array>
#include <vector>
#include <cmath> // DELETE

class ScatterPlot : public Drawable{
	protected:
		std::string name = "CHANGE ME";
		std::vector<std::array<double,2>> points;

	public:
		ScatterPlot(Canvas* c) : Drawable(c) {
			for(double i(-10); i <= 10; i += 0.1){
				points.push_back({i, sin(i)});
			}
		}

		virtual void draw(void) override{ canvas->draw(*this); }

		std::vector<std::array<double,2>> getPoints(void) const{ return points; }

		std::ostream& print(std::ostream &output) const;
};
