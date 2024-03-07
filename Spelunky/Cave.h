#pragma once
#include <vector>


class Room;

class Cave
{
public:
	Cave();
	~Cave();
	void Draw() const;
	const static int room_size_x{4};
	const static int room_size_y{4};


private:
	std::vector<Room*> m_Rooms;
	void GenerateRooms();
	int GetRoomIndex(int x, int y) const;
};

