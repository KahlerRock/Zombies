#pragma once
#include <map>
#include <string>
#include "TextureManagerHeader.hpp"
#include "Vector2D.hpp"
#include "ECS/ECS.hpp"
#include "SDL_ttf.h"

class AssetManager : public Component
{
public:
	AssetManager(Manager *man);
	~AssetManager();

	void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, double angle, std::string id);
	void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);

	Entity &CreatePlayer(float x, float y, float speed);

	void AddTexture(std::string id, const char *path);

	SDL_Texture *GetTexture(std::string id);

	void AddFont(std::string id, std::string path, int fontsize);

	TTF_Font *GetFont(std::string id);

private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
};