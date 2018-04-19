#include "AssetManager.hpp"
#include "ECS\Components.hpp"
#include "Math.h"


AssetManager::AssetManager(Manager *man) : manager(man)
{}

AssetManager::~AssetManager() {}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, double angle, std::string id)
{
	
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, BLOCK_SIZE, BLOCK_SIZE, 1);
	projectile.addComponent<SpriteComponent>(id, true);
	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);
}
void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
	vel.x *= speed;
	vel.y *= speed;
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, BLOCK_SIZE, BLOCK_SIZE, 1);
	projectile.addComponent<SpriteComponent>(id, true);
	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);
}

Entity &AssetManager::CreatePlayer(float x, float y, float speed)
{
	Player player = Player(manager, x, y, speed);
	Entity &p = player.getPlayer();
	p.getComponent<TransformComponent>().oldPos = Vector2D(x, y);
	p.setHP(100);
	return p;
}

void AssetManager::AddTexture(std::string id, const char *path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture *AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontsize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontsize));
}

TTF_Font * AssetManager::GetFont(std::string id)
{
	return fonts[id];
}