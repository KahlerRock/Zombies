#pragma once

#include "Components.hpp"
#include "SDL.h"
#include "../TextureManagerHeader.hpp"
#include "Animation.hpp"
#include "../AssetManager.hpp"
#include <map>
class SpriteComponent : public Component
{
private:
	TransformComponent * transform;
	SDL_Texture *texture;
	SDL_Rect srcR, destR;

	bool animated = false;
	int frames = 0, speed = 100;

public:

	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(std::string id)
	{
		setTex(id);
	}

	SpriteComponent(std::string id, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 1, 100);
		Animation walk = Animation(0, 4, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);
		if (animated)
			Play("Walk");
		else
			Play("Idle");

		setTex(id);
	}

	~SpriteComponent()
	{
	}

	void setTex(std::string id)
	{
		texture = Game::assets->GetTexture(id);
	}

	void init() override
	{
		transform = &ent->getComponent<TransformComponent>();

		srcR.x = srcR.y = 0;
		srcR.w = transform->width;
		srcR.h = transform->height;

	}

	void update() override
	{
		if (animated)
		{
			srcR.x = srcR.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcR.y = animIndex * transform->height;
		destR.x = static_cast<int>(transform->position.x - Game::camera.x);
		destR.y = static_cast<int>(transform->position.y - Game::camera.y);
		destR.w = transform->width * transform->scale;
		destR.h = transform->height * transform->scale;
	}

	SDL_Texture *getTex()
	{
		return texture;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcR, destR, spriteFlip);
	}

	void Play(const char *animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};