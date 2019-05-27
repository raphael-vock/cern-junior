#pragma once
#include <string>
#include <iostream>

#include "accelerator.h"

namespace cli{
	std::string tolower(std::string str);
	void try_again(void);

	template <typename T>
	T getInput(std::string message){
		std::cout << message;
		T input;
		do{
			try_again();
			std::cin >> input;
		}while(std::cin.fail());
		return input;
	}

	void add_beams(Accelerator& w);
}
