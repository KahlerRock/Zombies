#pragma once
#include "GameHeader.hpp"
class GameObject
{
public:
	GameObject(const char *textureSheet, int x, int y);
	~GameObject();

	void Update();
	void Render();

private:
	int xpos, ypos;

	SDL_Texture *objTex;
	SDL_Rect srcR, destR;
	SDL_Renderer *renderer;
};