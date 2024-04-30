#pragma once
#include <array>
#include <vector>
#include "PathTypes.h"
#include "Vector2i.h"
#include "Tile.h"

class SpriteSheetManager;
enum class TileTypes;

struct ExtraPathInformation
{
	Vector2i entranceLocation;
	Vector2i exitLocation;
};

class Cave final
{
public:
	explicit Cave(WorldManager* worldManager);
	virtual ~Cave() = default;
	Cave(const Cave& other) = delete;
	Cave& operator=(const Cave& other) = delete;
	Cave(Cave && other) = delete;
	Cave& operator=(Cave&& other) = delete;

	
	void Draw() const;
	void GenerateLevel();
	Vector2f GetEntrance() const;
	Vector2f GetExit() const;
	const std::vector<std::vector<Tile>>* GetTiles() const;
	const static int MAX_ROOMS_X{4};
	const static int MAX_ROOMS_Y{4};
	const static int TILES_PER_ROOM_X{10};
	const static int TILES_PER_ROOM_Y{8};
	const static int TILES_BORDER_X{2};
	const static int TILES_BORDER_Y{2};
	const static int CAVE_GENERATOR_TILE_COUNT_X{MAX_ROOMS_X * TILES_PER_ROOM_X};
	const static int CAVE_GENERATOR_TILE_COUNT_Y{MAX_ROOMS_Y * TILES_PER_ROOM_Y};
	const static int CAVE_TILE_COUNT_X{MAX_ROOMS_X * TILES_PER_ROOM_X + TILES_BORDER_X * 2};
	const static int CAVE_TILE_COUNT_Y{MAX_ROOMS_Y * TILES_PER_ROOM_Y + TILES_BORDER_Y * 2};
	

private:
	SpriteSheetManager* m_SpriteSheetManager;
	std::vector<std::vector<Tile>> m_Tiles;

	Vector2f m_EntranceLocation;
	Vector2f m_ExitLocation;
	
	std::array<std::array<PathTypes, MAX_ROOMS_Y>, MAX_ROOMS_X> m_PathDebug;
	ExtraPathInformation m_InfoDebug;
	void GenerateTiles(std::array<std::array<TileTypes,CAVE_GENERATOR_TILE_COUNT_Y>, CAVE_GENERATOR_TILE_COUNT_X>& tileArray);
	void GeneratePath(std::array<std::array<PathTypes, MAX_ROOMS_Y>, MAX_ROOMS_X>& roomPath, ExtraPathInformation& extraInfo);
	void RoomStringToTileType(const std::string* roomString, std::array<std::array<TileTypes, Cave::CAVE_GENERATOR_TILE_COUNT_Y>, Cave::CAVE_GENERATOR_TILE_COUNT_X> &tileTypes, Vector2i roomLocation);
	std::string RoomStringPreprocessor(std::string strCopy);
};
