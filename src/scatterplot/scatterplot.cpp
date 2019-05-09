#include "scatterplot.h"

std::ostream& ScatterPlot::print(std::ostream &output) const{
	output << name << ":";
	for(const auto &x : points){
		output << x[0] << "," << x[1] << "\n";
	}
	return output;
}
