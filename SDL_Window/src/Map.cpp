#include "Map.hpp"
#include "GameHeader.hpp"
#include "ECS/ECS.hpp"
#include "ECS/Components.hpp"
#include <fstream>

extern Manager manager;
Map::Map(std::string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts) 
{
	scaledSize = ms * ts;
}

Map::~Map() {}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);


	int srcX, srcY;
	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;
			AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
			mapFile.ignore();
		}
		mapFile.ignore();
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			mapFile.get(c);
			if (c == '1')
			{ 
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
				
			}
			if (c == 'J') {
				//std::cout << "Juggernog Placed\n";
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("jugg", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			if (c == 'S') {
				//std::cout << "Swift Soda Placed\n";
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("swiftsoda", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			if (c == 'R') {
				//std::cout << "Rapid Reload Placed\n";
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("rapidreload", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
		mapFile.ignore();
	}

	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto &tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
	tile.addGroup(Game::groupMap);
}

void Map::GetTileCoords(std::string path, char desiredTile, int *xCoord, int* yCoord) {
	char c;
	std::fstream mapFile;
	mapFile.open(path);
	int jump = MAP_HEIGHT * MAP_WIDTH;

	for (int y = 0; y < MAP_HEIGHT*2; y++) {
		for (int x = 0; x < MAP_WIDTH*2; x++) {
			mapFile.get(c);

			if (c == desiredTile) {
				*xCoord = x;
				*yCoord = y;
			}
		}
	}	
}