#pragma once

#include <string>
#include <iostream>

// Some functions for parsing console input:

std::string tolower(std::string str){
	for(char &c : str) c = tolower(c);
	return str;
}

void try_again(void){
	if(not std::cin.fail()) return;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	std::cout << "Come again?\n";
}

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
