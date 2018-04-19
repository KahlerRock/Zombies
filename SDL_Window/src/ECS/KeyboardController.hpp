#pragma once
#include "../GameHeader.hpp"
#include "ECS.hpp"
#include "Components.hpp"
#include <cmath>

class KeyboardController : public Component
{
public:
	TransformComponent *transform;
	SpriteComponent *sprite;

	void init() override
	{
		transform = &ent->getComponent<TransformComponent>();
		sprite = &ent->getComponent<SpriteComponent>();
	}
	const Uint8 *keystate;
	Uint64 time = 1, start;
	Vector2D cursor, angle, angleNorm;
	long double angleF;
	int bullets = 10;
	bool pressed = false;
	bool first = true;

	void update() override
	{
		
		start = SDL_GetTicks();
		if (keystate = SDL_GetKeyboardState(NULL))
		{
			if (keystate[SDL_SCANCODE_W])
			{
				transform->velocity.y = -1;
				sprite->setTex("playerU");
			}
			if (keystate[SDL_SCANCODE_A])
			{
				sprite->setTex("playerL");
				transform->velocity.x = -1;
			}
			if (keystate[SDL_SCANCODE_S])
			{
				sprite->setTex("playerD");
				transform->velocity.y = +1;
			}
			if (keystate[SDL_SCANCODE_D])
			{
				sprite->setTex("playerR");
				transform->velocity.x = 1;
			}
			if(keystate[SDL_SCANCODE_LSHIFT])
					transform->speed = 10.0f;
			if (keystate[SDL_SCANCODE_R])
				bullets = 10;				
		}
		switch(Game::event.type)
		{
		case SDL_KEYUP:
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				sprite->Play("Idle");
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				sprite->Play("Idle");
				transform->velocity.x = 0;
				break;
			case SDLK_s:
				sprite->Play("Idle");
				transform->velocity.y = 0;
				break;
			case SDLK_d:
				sprite->Play("Idle");
				transform->velocity.x = 0;
				break;
			case SDLK_LSHIFT:
				transform->speed = 5.0f;
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			default:
				break;
			}
		case SDL_MOUSEMOTION:
			
			break;
		case SDL_MOUSEBUTTONDOWN:			
			cursor.x = Game::event.motion.x + Game::camera.x;
			cursor.y = Game::event.motion.y + Game::camera.y;
			angle = cursor - transform->position;
			angleF = sqrt(angle.x * angle.x + angle.y * angle.y);
			angleNorm.x = angle.x / angleF;
			angleNorm.y = angle.y / angleF;
			std::cout << transform->position << std::endl;
			if (bullets != 0 && !pressed)
			{
				if(angleNorm.x > 0 && abs(angleNorm.x) > abs(angleNorm.y))
					Game::assets->CreateProjectile(transform->position, angleNorm, 200, 10, "projectileR");
				else if (angleNorm.x < 0 && abs(angleNorm.x) > abs(angleNorm.y))
					Game::assets->CreateProjectile(transform->position, angleNorm, 200, 10, "projectileL");
				else if( angleNorm.y > 0 && abs(angleNorm.x) < abs(angleNorm.y))
					Game::assets->CreateProjectile(transform->position, angleNorm, 200, 10, "projectileD");
				else if(angleNorm.y < 0 && abs(angleNorm.x) < abs(angleNorm.y))
					Game::assets->CreateProjectile(transform->position, angleNorm, 200, 10, "projectileU");
				bullets--;
				pressed = true;
			}				
			break;
		case SDL_MOUSEBUTTONUP:			
			pressed = false;
			break;
		default:
			break;
		}
		time = SDL_GetTicks() - start;
	}

};