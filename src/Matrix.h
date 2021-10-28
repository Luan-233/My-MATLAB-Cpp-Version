#pragma once

class Matrix {
private:
	double** Value;
	int x_length, y_length;

public:
	void Copy_Matrix(const Matrix& x);

	Matrix();
	Matrix(int X, int Y);
	Matrix(int X, int Y, const char type);
	Matrix(const Matrix& x);
	Matrix& operator = (const Matrix& x);

	~Matrix();

	int GetX();
	int GetY();
	bool IsNULL();
	bool IsSquare();

	void Show();

	void Init();
	void Init(int X, int Y, double Value);

	Matrix Inverse();
	Matrix T();

	int Rank();
	double Det();

	Matrix operator + (const Matrix& x) const;
	Matrix operator - (const Matrix& x) const;
	Matrix operator * (const Matrix& x) const;
	Matrix operator ^ (int x) const;
};