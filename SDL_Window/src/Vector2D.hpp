#pragma once
#include <iostream>

class Vector2D
{
public:

	long double x, y;

	Vector2D();
	Vector2D(long double x, long double y);

	long double Length();

	Vector2D Normalize();

	Vector2D &Add(const Vector2D &vec);
	Vector2D &Subtract(const Vector2D &vec);
	Vector2D &Multiply(const Vector2D &vec);
	Vector2D &Divide(const Vector2D &vec);

	friend Vector2D &operator+(Vector2D &v1, Vector2D &v2);
	friend Vector2D &operator-(Vector2D &v1, Vector2D &v2);
	friend Vector2D &operator*(Vector2D &v1, Vector2D &v2);
	friend Vector2D &operator/(Vector2D &v1, Vector2D &v2);

	Vector2D &operator+=(const Vector2D &vec);
	Vector2D &operator-=(const Vector2D &vec);
	Vector2D &operator*=(const Vector2D &vec);
	Vector2D &operator/=(const Vector2D &vec);

	Vector2D &operator*(const int& i);
	Vector2D &Zero();

	friend std::ostream &operator<<(std::ostream &stream, const Vector2D &vec);

};