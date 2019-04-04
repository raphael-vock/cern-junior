#pragma once

#include <iostream>

#include "textview.h"
#include "../accelerator/accelerator.h"

class ConsoleWidget : public Accelerator{
	public:
		ConsoleWidget(Vector3D origin) : Accelerator(new TextView(std::cout), origin){ std::cout << "\n"; }

		void show(void){ print(std::cout, true); }
};
