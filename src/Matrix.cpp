#pragma once

#include "Matrix.h"

#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>

#define EPS 1e-5

void Matrix::Copy_Matrix(const Matrix& x) {
	if (this->Value != NULL) {
		for (int i = 0; i < this->x_length; ++i) delete[] this->Value[i];
		delete[] this->Value;
	}
	this->x_length = x.x_length, this->y_length = x.y_length;
	Value = new double* [this->x_length];
	for (int i = 0; i < this->x_length; ++i) this->Value[i] = new double[this->y_length];
}

Matrix::Matrix() {
	Value = NULL, x_length = 0, y_length = 0;
}

Matrix::Matrix(int X, int Y) {
	if ((!(X * Y))) { Value = NULL, x_length = 0, y_length = 0; return; }
	this->Value = new double* [X];
	for (int i = 0; i < X; ++i) this->Value[i] = new double[Y];
	this->x_length = X, this->y_length = Y;
	for (int i = 0; i < this->x_length; ++i) {
		for (int j = 0; j < this->y_length; ++j) this->Value[i][j] = 0.0;
	}
}

Matrix::Matrix(int X, int Y, const char type) {
	if ((!(X * Y))) { Value = NULL, x_length = 0, y_length = 0; return; }
	this->Value = new double* [X];
	for (int i = 0; i < X; ++i) this->Value[i] = new double[Y];
	this->x_length = X, this->y_length = Y;
	for (int i = 0; i < this->x_length; ++i) {
		for (int j = 0; j < this->y_length; ++j) this->Value[i][j] = 0.0;
	}
	switch (type) {
	case 'I':
		for (int i = 0; i < std::min(X, Y); ++i) this->Value[i][i] = (double)1.0;
		break;
	}//To be continued...
}

Matrix::Matrix(const Matrix& x) {
	this->x_length = x.x_length, this->y_length = x.y_length;
	Value = new double* [this->x_length];
	for (int i = 0; i < this->x_length; ++i) this->Value[i] = new double[this->y_length];
	for (int i = 0; i < this->x_length; ++i) {
		for (int j = 0; j < this->y_length; ++j) this->Value[i][j] = x.Value[i][j];
	}
}

Matrix& Matrix::operator = (const Matrix& x) {
	if (&x == this) return *this;
	if ((this->x_length != x.x_length) || (this->y_length != x.y_length)) Copy_Matrix(x);
	for (int i = 0; i < this->x_length; ++i) {
		for (int j = 0; j < this->y_length; ++j) this->Value[i][j] = x.Value[i][j];
	}
	return *this;
}

Matrix::~Matrix() {
	if (this->Value == NULL) return;
	for (int i = 0; i < this->x_length; ++i) delete[] this->Value[i];
	delete[] this->Value;
}

int Matrix::GetX() {
	return this->x_length;
}

int Matrix::GetY() {
	return this->y_length;
}

bool Matrix::IsNULL() {
	return (!(this->x_length | this->y_length));
}

bool Matrix::IsSquare() {
	return (!(this->x_length ^ this->y_length));
}

void Matrix::Show() {
	if (IsNULL()) { std::puts("The matrix is empty."); return; }
	for (int i = 0; i < this->x_length; ++i) {
		for (int j = 0; j < this->y_length; ++j) {
			std::cout << std::fixed << std::setprecision(6) << this->Value[i][j] << " ";
		}
		std::puts("");
	}
}

void Matrix::Init() {
	for (int i = 0; i < this->x_length; ++i) {
		for (int j = 0; j < this->y_length; ++j) std::cin >> this->Value[i][j];
	}
}

void Matrix::Init(int X, int Y, double Value) { this->Value[X][Y] = Value; }

Matrix Matrix::Inverse() {
	Matrix X0 = Matrix(*this);
	Matrix X1 = Matrix(this->x_length, this->y_length, 'I');
	for (int i = 0; i < this->x_length; ++i) {
		if (std::fabs(X0.Value[i][i]) < EPS) {
			int pos = 0;
			for (int j = i + 1; j < this->x_length; ++j) {
				if (fabs(this->Value[j][i]) > EPS) { pos = j; break; }
			}
			for (int j = 0; j < this->x_length; ++j) {
				std::swap(X0.Value[i][j], X0.Value[pos][j]);
				std::swap(X1.Value[i][j], X1.Value[pos][j]);
			}
		}
		double tmp = X0.Value[i][i];
		for (int j = 0; j < this->y_length; ++j) X0.Value[i][j] /= tmp, X1.Value[i][j] /= tmp;
		for (int j = i + 1; j < this->x_length; ++j) {
			tmp = X0.Value[j][i];
			for (int k = 0; k < this->y_length; ++k) {
				X0.Value[j][k] = X0.Value[j][k] - X0.Value[i][k] * tmp;
				X1.Value[j][k] = X1.Value[j][k] - X1.Value[i][k] * tmp;
			}
		}
	}
	for (int i = this->x_length - 1; i; --i) {
		for (int j = i - 1; ~j; --j) {
			for (int k = 0; k < this->x_length; ++k) X1.Value[j][k] -= X1.Value[i][k] * X0.Value[j][i];
		}
	}
	return X1;
}

Matrix Matrix::T() {
	Matrix X0 = Matrix(this->y_length, this->x_length);
	for (int i = 0; i < this->x_length; ++i) {
		for (int j = 0; j < this->y_length; ++j) X0.Value[j][i] = this->Value[i][j];
	}
	return X0;
}

int Matrix::Rank() {
	int res = 0, pre = -1;
	Matrix X0 = Matrix(*this);
	for (int i = 0; i < X0.x_length; ++i) {
		int pos = -1;
		while ((!(~pos)) && (pre < X0.y_length)) {
			++pre;
			for (int j = i; j < X0.x_length; ++j) {
				if (fabs(X0.Value[j][pre]) > EPS) { pos = j; break; }
			}
		}
		if (!(~pos)) return res;
		++res;
		if (i != pos) {
			for (int j = 0; j < X0.y_length; ++j) std::swap(X0.Value[i][j], X0.Value[pos][j]);
		}
		for (int j = X0.y_length - 1; j >= pre; --j) X0.Value[i][j] /= X0.Value[i][pre];
		for (int j = i + 1; j < X0.x_length; ++j) {
			double tmp = X0.Value[j][pre];
			for (int k = pre; k < X0.y_length; ++k) X0.Value[j][k] -= tmp * X0.Value[i][k];
		}
	}
	return res;
}

double Matrix::Det() {
	double res = 1.0;
	Matrix X0 = Matrix(*this);
	for (int i = 0; i < this->x_length; ++i) {
		for (int j = i + 1; j < this->y_length; ++j) {
			if (std::fabs(X0.Value[i][i]) < EPS) {
				int pos = -1;
				for (int k = i + 1; k < this->x_length; ++k) {
					if (std::fabs(X0.Value[k][i]) > EPS) { pos = k; break; }
				}
				if (~pos) {
					for (int k = 0; k < this->x_length; ++k) std::swap(X0.Value[i][k], X0.Value[pos][k]);
					res *= -1.0;
				}
				else return (res = 0.0);
			}
			double f = X0.Value[j][i] / X0.Value[i][i];
			for (int k = i; k < this->x_length; ++k) X0.Value[j][k] -= X0.Value[i][k] * f;
		}
	}
	for (int i = 0; i < x_length; ++i) res *= X0.Value[i][i];
	return res;
}

Matrix Matrix::operator + (const Matrix& x) const {
	Matrix res = Matrix(this->x_length, this->y_length);
	for (int i = 0; i < this->x_length; ++i) {
		for (int j = 0; j < this->y_length; ++j) {
			res.Value[i][j] = this->Value[i][j] + x.Value[i][j];
		}
	}
	return res;
}

Matrix Matrix::operator - (const Matrix& x) const {
	Matrix res = Matrix(this->x_length, this->y_length);
	for (int i = 0; i < this->x_length; ++i) {
		for (int j = 0; j < this->y_length; ++j) {
			res.Value[i][j] = this->Value[i][j] - x.Value[i][j];
		}
	}
	return res;
}

Matrix Matrix::operator * (const Matrix& x) const {
	Matrix res = Matrix(this->x_length, x.y_length);
	for (int i = 0; i < this->x_length; ++i) {
		for (int j = 0; j < x.y_length; ++j) {
			res.Value[i][j] = 0;
			for (int k = 0; k < this->y_length; ++k) {
				res.Value[i][j] += this->Value[i][k] * x.Value[k][j];
			}
		}
	}
	return res;
}

Matrix Matrix::operator ^ (int x) const {
	if (!x) return Matrix(this->x_length, this->y_length, 'I');
	if (x < 0) {

	}
	else {

	}//To be continued...
}