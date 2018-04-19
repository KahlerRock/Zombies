#include "GameObjectHeader.hpp"
#include "TextureManagerHeader.hpp"

GameObject::GameObject(const char *textureSheet, int x, int y)
{
	objTex = TextureManager::LoadTexture(textureSheet);

	xpos = x, ypos = y;
}

GameObject::~GameObject(){}

void GameObject::Update()
{
	xpos = 0;
	ypos = 0;

	srcR.h = 16;
	srcR.w = 16;
	srcR.x = 0;
	srcR.y = 0;

	destR.x = xpos++;
	destR.y = ypos++;
	destR.w = srcR.w * 2;
	destR.h = srcR.h * 2;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTex, &srcR, &destR);
}