#pragma once

#include "ECS.hpp"
#include "Components.hpp"
#include "../Vector2D.hpp"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int rng, int sp, Vector2D vel) : range(rng), speed(sp), velocity(vel) {}
	~ProjectileComponent() {}

	void init() override
	{
		transform = &ent->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void update() override
	{
		distance += speed;
		if (distance > range)
		{
			//std::cout << "out of range!\n";
			ent->destroy();
		}
		else if (transform->position.x > Game::camera.x + Game::camera.w ||
			transform->position.x < Game::camera.x ||
			transform->position.y > Game::camera.y + Game::camera.h ||
			transform->position.y < Game::camera.y)
		{
			//std::cout << "Out of bounds!\n";
			ent->destroy();
		}
	}

private:

	TransformComponent * transform;
	int range, distance;
	long double speed;
	Vector2D velocity;
};
