#pragma once

#include "ECS.hpp"
#include "../Vector2D.hpp"
#include "../GameHeader.hpp"
#include "../TextureManagerHeader.hpp"

class TileComponent : public Component
{
public:

	SDL_Texture * texture;
	SDL_Rect srcR, destR;
	Vector2D position;

	TileComponent() = default;
	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id)
	{
		texture = Game::assets->GetTexture(id);

		position.x = xpos;
		position.y = ypos;

		srcR.x = srcX;
		srcR.y = srcY;
		srcR.w = srcR.h = tsize;

		destR.x = xpos;
		destR.y = ypos;
		destR.w = destR.h = tsize * tscale;
	}

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}


	void update() override
	{
		destR.x = static_cast<int>(position.x - Game::camera.x);
		destR.y = static_cast<int>(position.y - Game::camera.y);
	}
	void draw() override
	{
		TextureManager::Draw(texture, srcR, destR, SDL_FLIP_NONE);
	}

};