#pragma once

#include <cstring>
#include <iostream>

using std::string;

class Error {
private:
	char Input;

public:
	void Input_Error();
	void Matrix_Not_Exist();
	void Out_Of_Range();

	bool Get_Input();

	bool Query_To_Replace_Matrix(const string& Name);
	bool Query_To_Replace_Matrix();
	bool Query_To_Define_Matrix();
};