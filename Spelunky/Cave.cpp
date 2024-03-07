#include "pch.h"
#include "Cave.h"

#include "Room.h"

// Each Cave or gird of rooms. Is 4x4

Cave::Cave()
{
	GenerateRooms();
}

Cave::~Cave()
{
	for (int i{}; i < m_Rooms.size(); ++i)
	{
		delete m_Rooms[i];
	}
}

void Cave::Draw() const
{
	for (int i{}; i < m_Rooms.size(); ++i)
	{
		m_Rooms[i]->TestDrawRoom();
	}
}

void Cave::GenerateRooms()
{
	Vector2f currentRoomPosition = Vector2f{float(rand()%4), 4};

	bool generatingRooms = true;
	while (generatingRooms)
	{
		// Vector2f left = Vector2f{-1,0};
		// Vector2f down = Vector2f{0,-1};
		// Vector2f right = Vector2f{1,0};

		int x;
		int y;

		switch (rand()%3)
		{
		case 0:
			x = -1;
			y = 0;
			break;
		case 1:
			x = 0;
			y = -1;
			break;
		case 2:
			x = 1;
			y = 0;
			break;
		default:
			throw;
		}

		if(GetRoomIndex(x, y) == -1)

		generatingRooms = false;
	}

	


	m_Rooms.push_back(new Room{RoomDirection{false, false, false, false}, Vector2f{10,10}});

}

int Cave::GetRoomIndex(int x, int y) const
{
	if(x > 4 || y > 4) return -1;

	return y * room_size_x + x;

}
