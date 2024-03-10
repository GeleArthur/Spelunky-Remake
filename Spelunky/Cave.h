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
	const static int MAX_ROOM_SIZE_X{4};
	const static int MAX_ROOM_SIZE_Y{4};
	void CreateRoom();

private:
	std::vector<Room*> m_Rooms;
	void GenerateRoomTemplate(std::array<std::array<int,MAX_ROOM_SIZE_Y>, MAX_ROOM_SIZE_X> &roomPath);
	int GetRoomIndex(Vector2i v) const;
};

