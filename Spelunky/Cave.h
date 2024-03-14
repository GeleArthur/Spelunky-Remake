#pragma once
#include <array>
#include <vector>

#include "PathTypes.h"
#include "Tile.h"


struct Vector2i;
class Room;

class Cave
{
public:
	Cave();
	~Cave();
	void Draw() const;
	const static int MAX_ROOMS_X{4};
	const static int MAX_ROOMS_Y{4};
	const static int TILES_PER_ROOM_X{10};
	const static int TILES_PER_ROOM_Y{8};
	const static int MAX_CAVE_TILE_COUNT_X{MAX_ROOMS_X*TILES_PER_ROOM_X};
	const static int MAX_CAVE_TILE_COUNT_Y{MAX_ROOMS_Y*TILES_PER_ROOM_Y};

private:
	std::array<std::array<Tile, MAX_CAVE_TILE_COUNT_Y>, MAX_CAVE_TILE_COUNT_X> m_Tiles;
	
	void GenerateCave(std::array<std::array<TileTypes,MAX_CAVE_TILE_COUNT_Y>, MAX_CAVE_TILE_COUNT_X> &roomPath);
	void GeneratePath(std::array<std::array<PathTypes, MAX_ROOMS_Y>, MAX_ROOMS_X> &roomPath);
};
