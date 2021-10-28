#pragma once

#include "Error.h"
#include "Matrix.h"

#include <map>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

#define EPS 1e-5
#define INF 2147483647

#define debug(x) std::cout<< x <<std::endl

using std::map;
using std::pair;
using std::string;
using std::make_pair;

static const unsigned int SIZE = sizeof(double);

template<typename T> inline T min(T x, T y) { return (x < y) ? x : y; }
template<typename T> inline T max(T x, T y) { return (x > y) ? x : y; }

template<typename T> inline void read(T& x) {
	x = 0; char c = std::getchar();
	while ((!std::isdigit(c)) && (!std::isalpha(c))) c = std::getchar();
	while (std::isdigit(c)) x = (x * 10) + (c ^ 48), c = std::getchar();
	if (std::isalpha(c)) x = c;
}
template<typename T, typename... Ts>
inline void read(T& x, Ts&... xs) { read(x), read(xs...); }

template<typename T> void print(T x) {
	if (x < 0) std::putchar('-'), x = -x;
	if (x > 9) print(x / 10);
	std::putchar(x % 10 + 48);
}

static map<string, Matrix> Matrixs;
static map<string, Matrix>::iterator it, it1, it2;

static Matrix* Pos;
static Error Errors;
static char Option[225];

int main() {
	std::puts("Welcome to the simple-Matlab designed by Luan_233!");
	std::puts("Thank you for using it!");
	while (1) {
		std::cin >> Option;
		string Name, Ver, Name1, Name2;
		int X, Y;
		double Value;
		if (!std::strcmp(Option, "Define")) {
			std::cin >> Name >> X >> Y;
			if ((X <= 0) || (Y <= 0)) std::puts("The length is illegal in your input.");
			else if (X * Y > 300000) std::puts("The matrix is too big to be stored in memory.");
			else if (Matrixs.find(Name) != Matrixs.end()) {
				if (Errors.Query_To_Replace_Matrix(Name)) Matrixs[Name] = Matrix(X, Y);
			}
			else Matrixs[Name] = Matrix(X, Y);
		}
		else if (!std::strcmp(Option, "Show")) {
			std::cin >> Name;
			it = Matrixs.find(Name);
			if (it == Matrixs.end()) Errors.Matrix_Not_Exist();
			else (*it).second.Show();
		}
		else if (!std::strcmp(Option, "Modify")) {
			std::cin >> Name >> X >> Y >> Value;
			it = Matrixs.find(Name);
			if (it == Matrixs.end()) Errors.Matrix_Not_Exist();
			else {
				Pos = &((*it).second);
				if ((X <= 0) || (Y <= 0) || ((*Pos).GetX() < X) || ((*Pos).GetY() < Y)) Errors.Out_Of_Range();
				else (*Pos).Init(X - 1, Y - 1, Value);
			}
		}
		else if (!std::strcmp(Option, "Init")) {
			std::cin >> Name;
			it = Matrixs.find(Name);
			if (it == Matrixs.end()) Errors.Matrix_Not_Exist();
			else {
				X = (*it).second.GetX(), Y = (*it).second.GetY();
				//std::cout << "You need to input the full " << X << "*" << Y << " matrix." << std::endl;
				(*it).second.Init();
			}
		}
		else if (!std::strcmp(Option, "Inverse")) {
			std::cin >> Name >> Ver;
			it = Matrixs.find(Name);
			if (it == Matrixs.end()) Errors.Matrix_Not_Exist();
			else {
				if (!(*it).second.IsSquare()) std::puts("This is not a square matrix");
				else if (std::fabs((*it).second.Det()) < EPS) {
					std::puts("This matrix is a singular matrix, which has no inverse.");
				}
				else if (Matrixs.find(Ver) != Matrixs.end()) {
					if (Errors.Query_To_Replace_Matrix(Ver)) Matrixs[Ver] = (*it).second.Inverse();
				}
				else Matrixs[Ver] = (*it).second.Inverse();
			}
		}
		else if (!std::strcmp(Option, "Rank")) {
			std::cin >> Name;
			it = Matrixs.find(Name);
			if (it == Matrixs.end()) Errors.Matrix_Not_Exist();
			else std::cout << "The rank of " << Name << " is " << (*it).second.Rank() << '.' << std::endl;
		}
		else if (!std::strcmp(Option, "Det")) {
			std::cin >> Name;
			it = Matrixs.find(Name);
			if (it == Matrixs.end()) Errors.Matrix_Not_Exist();
			else if (!(*it).second.IsSquare()) std::puts("This is not a square matrix");
			else std::cout << "The determinant of " << Name << " is " << (*it).second.Det() << '.' << std::endl;
		}
		else if (!std::strcmp(Option, "Calculate")) {
			std::cin >> Name1 >> Option[0] >> Name2 >> Ver;
			it1 = Matrixs.find(Name1), it2 = Matrixs.find(Name2);
			if ((it1 == Matrixs.end()) || (it2 == Matrixs.end())) Errors.Matrix_Not_Exist();
			else if ((Option[0] != '+') && (Option[0] != '-') && (Option[0] != '*')) {
				std::puts("The operator is illeagl in this programme.");
			}
			else {
				if (Matrixs.find(Ver) != Matrixs.end()) {
					if (Errors.Query_To_Replace_Matrix(Ver)) Matrixs[Ver] = Matrix();
				}
				bool flag = ((*it1).second.GetY() == (*it2).second.GetX());
				bool flag1 = ((*it1).second.GetX() == (*it2).second.GetX());
				bool flag2 = ((*it1).second.GetY() == (*it2).second.GetY());
				switch (Option[0]) {
				case '+':
					if (!(flag1 || flag2)) std::puts("The shape of two matrixs is not equal.");
					else Matrixs[Ver] = (*it1).second + (*it2).second;
					break;
				case '-':
					if (!(flag1 || flag2)) std::puts("The shape of two matrixs is not equal.");
					else Matrixs[Ver] = (*it1).second - (*it2).second;
					break;
				case '*':
					if (!flag) std::puts("The row number of first matrix is not equal to the line number of second matrix.");
					else Matrixs[Ver] = (*it1).second * (*it2).second;
					break;
				}
			}
		}
		else if (!std::strcmp(Option, "T")) {
			std::cin >> Name >> Ver;
			it = Matrixs.find(Name);
			if (it == Matrixs.end()) Errors.Matrix_Not_Exist();
			else {
				if (Matrixs.find(Ver) != Matrixs.end()) {
					if (Errors.Query_To_Replace_Matrix(Ver)) Matrixs[Ver] = (*it).second.T();
				}
				else Matrixs[Ver] = (*it).second.T();
			}
		}
		else if (!std::strcmp(Option, "Who")) {
			if (Matrixs.empty()) std::puts("There is no matrix in working area.");
			for (it = Matrixs.begin(); it != Matrixs.end(); ++it) {
				X = (*it).second.GetX(), Y = (*it).second.GetY();
				std::cout << (*it).first << ':' << X << '*' << Y << std::endl;
			}
		}
		else if (!std::strcmp(Option, "Quit")) break;
		else Errors.Input_Error();
	}
	std::system("pause");
	return 0;
}