#pragma once
#include "../GameHeader.hpp"
#include "Components.hpp"
class Player
{
public:

	Player(Manager *man, float x, float y, float sp) : speed(sp), posx(x), posy(y), manager(man), player(man->addEntity())
	{
		player.addComponent<TransformComponent>(x, y, 32, 32, ENTSCALE, speed);
		player.addComponent<SpriteComponent>("playerD", false);
		player.addComponent<KeyboardController>();
		player.addComponent<ColliderComponent>("player");
		player.addGroup(Game::groupPlayers);
		auto& projectile(manager->addEntity());

		projectile.addComponent<TransformComponent>(0, 0, BLOCK_SIZE, BLOCK_SIZE, 1);
		projectile.addComponent<SpriteComponent>("playerD", true);
		projectile.addComponent<ProjectileComponent>(1, speed, Vector2D(1, 1));
		projectile.addComponent<ColliderComponent>("projectile");
		projectile.addGroup(Game::groupProjectiles);
	}
	void setSpeed(float sp)
	{
		speed = sp;
	}
	void setPos(float x, float y)
	{
		posx = x;
		posy = y;
	}
	Entity &getPlayer()
	{
		return player;
	}
private:
	Manager * manager;
	Entity &player;
	TransformComponent *transform;
	float speed, posx, posy;
};
