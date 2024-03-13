#pragma once
#include <array>
#include <vector>

#include "Tile.h"
#include "Vector2i.h"


enum class RoomTypes;
class SpriteSheetManager;

enum class SpecialRoomConditions
{
	none,
	entrance,
	escape,
};

class Room
{
public:
	Room(const RoomTypes& type, const Vector2i& location, const SpecialRoomConditions special);

	void TestDrawRoom() const;
	void Draw() const;

private:
	RoomTypes m_RoomType;
	std::array<Tile, 80> m_Tiles{};

	// Random picked string
	// std::string m_Level 
	// {
	// 	"0000000000"
	// 	"0000000000"
	// 	"0000100000"
	// 	"0000000000"
	// 	"0008000000"
	// 	"0000000000"
	// 	"0000000000"
	// 	"1111111111"
	// };

	Vector2i m_RoomLocation;
	SpecialRoomConditions m_Conditions;
};
