#include "pch.h"
#include "Vector2.h"
#include <iostream>

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::operator float* ()
{
	return &val[0];
}

float Vector2::operator[](int index) const
{
	return val[index];
}

void Vector2::operator=(Vector2& other)
{
	x = other.x;
	y = other.y;
}

Vector2 Vector2::operator+(Vector2& other) const
{
	return { x + other.x, y + other.y };
}

void Vector2::operator+=(Vector2& other)
{
	x += other.x;
	y += other.y;
}

Vector2 Vector2::operator-(Vector2& other) const
{
	return { x - other.x, y - other.y };
}

void Vector2::operator-=(Vector2& other)
{
	x -= other.x;
	y -= other.y;
}

Vector2 Vector2::operator*(float scalar) const
{
	return { x * scalar, y * scalar };
}

void Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
}

Vector2 Vector2::operator/(float scalar) const
{
	return { x / scalar, y / scalar };
}

void Vector2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
}

float Vector2::MagnitudeSqr()
{
	return x * x + y * y;
}

float Vector2::Magnitude()
{
	return sqrtf(MagnitudeSqr());
}

float Vector2::DistanceSqr(Vector2 other)
{
	float diffX = x - other.x;
	float diffY = y - other.y;

	return diffX * diffX + diffY * diffY;
}

float Vector2::Distance(Vector2 other)
{
	return sqrtf(DistanceSqr(other));
}

void Vector2::Normalise()
{
	float mag = Magnitude();

	x /= mag;
	y /= mag;
}

Vector2 Vector2::Normalised()
{
	float mag = Magnitude();

	return { x / mag, y / mag };
}

float Vector2::Dot(Vector2 other)
{
	return x * other.x + y * other.y;
}

Vector2 Vector2::GetPerpendicularRH()
{
	return { -y, x };
}

Vector2 Vector2::GetPerpendicularLH()
{
	return { y, -x };
}

float Vector2::Angle(Vector2 other)
{
	Vector2 a = Normalised();
	Vector2 b = other.Normalised();

	return acos(a.Dot(b));
}