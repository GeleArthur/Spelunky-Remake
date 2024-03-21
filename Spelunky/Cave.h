#pragma once
#include <array>
#include <vector>
#include "PathTypes.h"
#include "Vector2i.h"

class SpriteSheetManager;
enum class TileTypes;
class Tile;

struct ExtraPathInformation
{
	Vector2i entranceLocation;
	Vector2i exitLocation;
};

class Cave
{
public:
	explicit Cave(SpriteSheetManager* spriteSheet);
	~Cave();
	void Draw() const;
	const std::vector<std::vector<Tile>>& GetTiles();
	const static int MAX_ROOMS_X{4};
	const static int MAX_ROOMS_Y{4};
	const static int TILES_PER_ROOM_X{10};
	const static int TILES_PER_ROOM_Y{8};
	const static int MAX_CAVE_TILE_COUNT_X{MAX_ROOMS_X*TILES_PER_ROOM_X};
	const static int MAX_CAVE_TILE_COUNT_Y{MAX_ROOMS_Y*TILES_PER_ROOM_Y};
	

private:
	std::vector<std::vector<Tile>> m_Tiles;
	SpriteSheetManager* m_SpriteSheetManager;

	// TODO: Group these
	Vector2f m_EntranceLocation;
	Vector2f m_ExitLocation;
	
	
	std::array<std::array<PathTypes, MAX_ROOMS_Y>, MAX_ROOMS_X> m_PathDebug;
	ExtraPathInformation m_InfoDebug;
	void GenerateTiles(std::array<std::array<TileTypes,MAX_CAVE_TILE_COUNT_Y>, MAX_CAVE_TILE_COUNT_X> &roomPath);
	void GeneratePath(std::array<std::array<PathTypes, MAX_ROOMS_Y>, MAX_ROOMS_X> &roomPath, ExtraPathInformation& extraInfo);
	void RoomStringToTileType(const std::string* roomString, std::array<std::array<TileTypes, Cave::MAX_CAVE_TILE_COUNT_Y>, Cave::MAX_CAVE_TILE_COUNT_X> &tileTypes, Vector2i roomLocation);
	std::string RoomStringPreprocessor(std::string strCopy);
};
