#include "GameHeader.hpp"
#include "TextureManagerHeader.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include <sstream>
Game::Game() {}
Game::~Game() {}



Map *map;
Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,SCREEN_W,SCREEN_H };

AssetManager *Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

SDL_Surface *surface = NULL;

SDL_Rect rect;


auto &label(manager.addEntity()); 
//auto &player(manager.addEntity());
Entity *player; 

bool immune = false;
int time = 0;
int health = 0;

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	scrW = width, scrH = height;
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL Initialized...\n";
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window Initialized...\n";
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Initailized...\n";
		}

		isRunning = true;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "Error: SDL_TTF failed to initialize.\n";
	}

	assets->AddTexture("terrain", "assets/terrainTiles.png");
	
	assets->AddTexture("projectileR", "assets/FireballR.png");
	assets->AddTexture("projectileL", "assets/FireballL.png");
	assets->AddTexture("projectileU", "assets/FireballU.png");
	assets->AddTexture("projectileD", "assets/FireballD.png");
	assets->AddTexture("playerD", "assets/UserHat.png");
	assets->AddTexture("playerR", "assets/UserHatR.png");
	assets->AddTexture("playerU", "assets/UserHatU.png");
	assets->AddTexture("playerL", "assets/UserHatL.png");

	assets->AddFont("terminator", "assets/terminat.ttf", 16);

	map = new Map("terrain", MAPSCALE, BLOCK_SIZE);

	map->LoadMap("assets/map.map", MAP_WIDTH, MAP_HEIGHT);

	int tmpX, tmpY;
	tmpX = tmpY = 0;

	map->GetTileCoords("assets/map.map", 'S', &tmpX, &tmpY);

	printf("X: %d, Y: %d \n", tmpX, tmpY);

	SDL_FillRect(surface, &rect, 255);

	player = &assets->CreatePlayer(100.0f, 100.0f, 5.0f);

	SDL_Color white = { 255,255,255,255 };
	SDL_Color black = { 0,0,0,255 };

	label.addComponent<UILabel>(10, 10, "Test String", "terminator", white);

	health = player->getHP();

}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;	
	default:
		break;
	}
}

void Game::update()
{
	if (immune)
		time++;
	SDL_Rect playerCol = player->getComponent<ColliderComponent>().collider;

	std::stringstream ss;
	ss << "Player position: " << player->getComponent<TransformComponent>().position;

	std::stringstream hp;
	hp << "HP: " << health;


	label.getComponent<UILabel>().SetLabelText(ss.str(), "terminator");
	label.getComponent<UILabel>().SetLabelText(hp.str(), "terminator");

	if (health < 1)
	{
		player->getComponent<TransformComponent>().position = Vector2D(-200, 200);
		label.getComponent<UILabel>().SetLabelText("Game Over!", "terminator");
		SDL_Delay(3000);
		isRunning = false;
	}

	bool collision = false;
	for (auto &c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			collision = true;
			if (!immune)
			{
				health -= 10;
				immune = true;
			}
		}
	}
	if (!collision)
	{
		player->getComponent<TransformComponent>().oldPos = player->getComponent<TransformComponent>().position;
	}
	else
	{
		player->getComponent<TransformComponent>().position = player->getComponent<TransformComponent>().oldPos;
	}

	for (auto &c : colliders)
	{
		for (auto &p : projectiles)
		{
			SDL_Rect eCol = c->getComponent<ColliderComponent>().collider;
			SDL_Rect pCol = p->getComponent<ColliderComponent>().collider;
			if (Collision::AABB(pCol, eCol))
			{
				p->destroy();
				c->destroy();
			}
		}
	}
	camera.x = (player->getComponent<TransformComponent>().position.x - (SCREEN_W / 2 - BLOCK_SIZE));
	camera.y = (player->getComponent<TransformComponent>().position.y - (SCREEN_H / 2 - BLOCK_SIZE));

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x >(MAP_WIDTH * BLOCK_SIZE * MAPSCALE) - camera.w)
		camera.x = (MAP_WIDTH * BLOCK_SIZE * MAPSCALE) - camera.w;
	if (camera.y >(MAP_HEIGHT * BLOCK_SIZE * MAPSCALE) - camera.h)
		camera.y = (MAP_HEIGHT * BLOCK_SIZE * MAPSCALE) - camera.h;
	if (time == 75)
	{
		time = 0;
		immune = false;
	}
	manager.refresh();
	manager.update();
}

void Game::render()
{
	SDL_RenderClear(renderer);

	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto &c : colliders)
	{
		c->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}
	
	for (auto& p : projectiles)
	{
		p->draw();
	}

	label.draw();



	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned...\n";
}