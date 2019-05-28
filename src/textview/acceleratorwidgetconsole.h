#pragma once

#include <iostream>

#include "textview.h"
#include "../physics/accelerator.h"

class AcceleratorWidgetConsole : public Accelerator{
	public:
		AcceleratorWidgetConsole(Vector3D origin) : Accelerator(new TextView(std::cout), origin){ std::cout << "\n"; }

		void show(void){ print(std::cout, true); }
};
