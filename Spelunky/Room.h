#pragma once
#include <vector>
#include "Vector2i.h"


struct RoomDirection
{
	bool isLeftOpen = false;
	bool isTopOpen = false;
	bool isDownOpen = false;
	bool isRightOpen = false;
};

enum class SpecialRoomConditions
{
	none,
	entrance,
	escape,
};

class Room
{
public:
	RoomDirection IsOpen() const;
	Room(const RoomDirection& dir, const Vector2i& location, SpecialRoomConditions special);

	void TestDrawRoom() const;

private:
	RoomDirection m_OpenDirection;

	// Random picked string
	std::string m_Level 
	{
		"6000060000"
		"0000000000"
		"0000000000"
		"0000000000"
		"0008000000"
		"0000000000"
		"0000000000"
		"1111111111"
	};
	 
	Vector2i m_RoomLocation;
	SpecialRoomConditions m_Conditions;



};

