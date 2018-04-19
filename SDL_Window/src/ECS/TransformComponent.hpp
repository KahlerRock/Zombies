#pragma once
#include "Components.hpp"
#include "../Vector2D.hpp"

class TransformComponent : public Component
{
public:

	Vector2D position;
	Vector2D velocity;

	Vector2D oldPos;

	int height = 32, width = 32, scale = 1;

	long double speed = 10.0f;

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(int sc)
	{
		position.Zero();
		scale = sc;
	}

	TransformComponent(long double x, long double y)
	{
		position.Zero();
	}

	TransformComponent(long double x, long double y, int w, int h, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}
	TransformComponent(long double x, long double y, int w, int h, int sc, int sp) : speed(sp)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override
	{
		velocity.Zero();
	}

	void update() override
	{
		position.x += (velocity.x * speed);
		position.y += (velocity.y * speed);
	}
};