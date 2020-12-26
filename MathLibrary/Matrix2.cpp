#include "Matrix2.h"

const Matrix2 Matrix2::Identity
{
	Vector2(1, 0),
	Vector2(0, 1)
};

Matrix2::Matrix2()
{
	*this = Identity;
}

Matrix2::Matrix2(Vector2 col0, Vector2 col1)
{
	vec[0] = col0;
	vec[1] = col1;
}

Matrix2::operator float* ()
{
	return &val[0][0];
}

Vector2 Matrix2::operator[](int col)
{
	return vec[col];
}

void Matrix2::operator=(Matrix2 other)
{
	for (int i = 0; i < 2; ++i)
		vec[i] = other.vec[i];
}

Matrix2 Matrix2::operator*(Matrix2& other) const
{
	Matrix2 result;



	return result;
}
