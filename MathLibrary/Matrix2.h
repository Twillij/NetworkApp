#pragma once
#include "Vector2.h"

class Matrix2
{
public:
	Matrix2();
	Matrix2(Vector2 col0, Vector2 col1);
	~Matrix2() {}

	union
	{
		float val[2][2];
		Vector2 vec[2];
	};

	operator float* ();
	Vector2 operator[](int col);
	void operator=(Matrix2 other);
	Matrix2 operator*(Matrix2& other) const;
	Vector2 operator*(Vector2& vec2) const;

	static const Matrix2 Identity;
};