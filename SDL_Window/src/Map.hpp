#pragma once
#include <string>
class Map
{
public:

	Map(std::string tID, int ms, int ts);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);

	void GetTileCoords(std::string path, char desiredTile,int *xCoord, int *yCoords);

	void AddTile(int srcX, int srcY, int xpos, int ypos);
private:
	std::string texID;
	int mapScale;
	int tileSize;
	int scaledSize;

};