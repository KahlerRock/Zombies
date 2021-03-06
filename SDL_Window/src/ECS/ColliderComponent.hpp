#pragma once
#include <string>
#include "SDL.h"
#include "Components.hpp"
#include "../TextureManagerHeader.hpp"

class ColliderComponent : public Component
{
public:

	SDL_Rect collider;
	std::string tag;

	SDL_Texture *tex;
	SDL_Rect srcR, destR;

	TransformComponent *transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}

	void init() override
	{
		if (!ent->hasComponent<TransformComponent>())
			ent->addComponent<TransformComponent>();

		transform = &ent->getComponent<TransformComponent>();

		if (tag == "jugg") {
			tex = TextureManager::LoadTexture("assets/Perks/jugg.png");
		}else if (tag == "swiftsoda") {
			tex = TextureManager::LoadTexture("assets/Perks/swiftsoda.png");
		}else if (tag == "rapidreload") {
			tex = TextureManager::LoadTexture("assets/Perks/rapidreload.png");
		}
		else {
			tex = TextureManager::LoadTexture("assets/coltex.png");
		}

		srcR = { 0,0,32,32 };
		destR = { collider.x, collider.y, collider.w, collider.h };



	}

	void update() override
	{
		if (tag != "terrain" && tag != "jugg" && tag != "swiftsoda" && tag != "rapidreload")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}
		
		destR.x = collider.x - Game::camera.x;
		destR.y = collider.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);

	}
};