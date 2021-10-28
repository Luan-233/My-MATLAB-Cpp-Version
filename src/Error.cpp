#pragma once

#include "Error.h"

#include <cstdio>
#include <cstring>
#include <iostream>

using std::string;

void Error::Input_Error() {
	std::puts("Wrong Input!");
}

void Error::Matrix_Not_Exist() {
	std::puts("The Matrix that you need is not existed.");
}

void Error::Out_Of_Range() {
	std::puts("The point is out of this matrix.");
}

bool Error::Get_Input() {
	do {
		std::cin >> Input;
		if (Input == 'Y') return true;
		else if (Input == 'N') return false;
		else Input_Error(), std::puts("Please input again!");
	} while ((Input != 'Y') && (Input != 'N'));
	return false;
}

bool Error::Query_To_Replace_Matrix(const string& Name) {
	std::cout << "The matrix " << Name << " has been defined." << std::endl;
	std::puts("Do you want to replace it? (Y/N)");
	return Get_Input();
}

bool Error::Query_To_Replace_Matrix() {
	std::puts("The matrix has been defined.");
	std::puts("Do you want to replace it? (Y/N)");
	return Get_Input();
}

bool Error::Query_To_Define_Matrix() {
	std::puts("Do you want to define it? (Y/N)");
	return Get_Input();
}