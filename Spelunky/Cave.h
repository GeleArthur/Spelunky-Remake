#pragma once
#include <vector>


struct Vector2i;
class Room;

class Cave
{
public:
	Cave();
	~Cave();
	void Draw() const;
	const static int MAX_ROOM_SIZE_X{3};
	const static int MAX_ROOM_SIZE_Y{3};


private:
	std::vector<Room*> m_Rooms;
	void GenerateRooms();
	int GetRoomIndex(Vector2i v) const;
};

