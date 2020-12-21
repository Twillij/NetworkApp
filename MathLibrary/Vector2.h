#pragma once

class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	~Vector2() {}

	union
	{
		float val[2];
		struct { float x, y; };	
	};

	operator float* ();

	float operator[](int index) const;

	void operator=(Vector2& other);

	Vector2 operator+(Vector2& other) const;
	void operator += (Vector2& other);

	Vector2 operator - (Vector2& other) const;
	void operator -= (Vector2& other);

	Vector2 operator * (float scalar) const;
	void operator *= (float scalar);

	Vector2 operator / (float scalar) const;
	void operator /= (float scalar);

	// calculates the distance of a vector from origin
	float MagnitudeSqr();
	float Magnitude();

	// calculates the distance from vector A to vector B
	float DistanceSqr(Vector2 other);
	float Distance(Vector2 other);

	// downscales a vector by its magnitude so that it is within a unit circle from the origin
	void Normalise();
	Vector2 Normalised();

	// returns the dot product of two vectors
	float Dot(Vector2 other);

	// returns a vector that is perpendicular to the argument vector
	Vector2 GetPerpendicularRH(); // right perpendicular
	Vector2 GetPerpendicularLH(); // left perpendicular

	// calculates the angle created by two vectors extended from the origin
	float Angle(Vector2 other);
};