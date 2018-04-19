#include "Vector2D.hpp"
#include <cmath>

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(long double x, long double y)
{
	this->x = x;
	this->y = y;
}

Vector2D &Vector2D::Add(const Vector2D &vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}

Vector2D &Vector2D::Subtract(const Vector2D &vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}

Vector2D &Vector2D::Multiply(const Vector2D &vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}

Vector2D &Vector2D::Divide(const Vector2D &vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;
}

Vector2D &operator+(Vector2D &v1, Vector2D &v2)
{
	return v1.Add(v2);
}

Vector2D &operator-(Vector2D &v1, Vector2D &v2)
{
	return v1.Subtract(v2);
}

Vector2D &operator*(Vector2D &v1, Vector2D &v2)
{
	return v1.Multiply(v2);
}

Vector2D &operator/(Vector2D &v1, Vector2D &v2)
{
	return v1.Divide(v2);
}

Vector2D &Vector2D::operator+=(const Vector2D &vec)
{
	return this->Add(vec);
}

Vector2D &Vector2D::operator-=(const Vector2D &vec)
{
	return this->Subtract(vec);
}

Vector2D &Vector2D::operator*=(const Vector2D &vec)
{
	return this->Multiply(vec);
}

Vector2D &Vector2D::operator/=(const Vector2D &vec)
{
	return this->Divide(vec);
}

Vector2D &Vector2D::operator*(const int &i)
{
	this->x *= i;
	this->y *= i;
	return *this;
}

Vector2D &Vector2D::Zero()
{
	this->x = 0;
	this->y = 0;
	return *this;
}

long double Vector2D::Length()
{
	return sqrt(x*x + y*y);
}

Vector2D Vector2D::Normalize()
{
	Vector2D vec;
	long double length = this->Length();

	if (length != 0)
	{
		vec.x = x / length;
		vec.y = y / length;
	}
	return vec;
}

std::ostream &operator<<(std::ostream &stream, const Vector2D &vec)
{
	stream << "( " << vec.x << ", " << vec.y << " )";
	return stream;
}

