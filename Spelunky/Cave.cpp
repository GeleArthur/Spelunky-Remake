#include "pch.h"
#include "Cave.h"

#include <array>
#include <iostream>

#include "Room.h"
#include "utils.h"
#include "Vector2i.h"

// Each Cave or gird of rooms. Is 4x4

Cave::Cave()
{
    CreateRoom();
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

enum class Direction
{
    left,
    right,
    down
};

// My guess right now
// 1 = left, right open
// 2 = left, right, bottom
// 3 = left, right, top


void Cave::GenerateRoomTemplate(std::array<std::array<int,MAX_ROOM_SIZE_Y>, MAX_ROOM_SIZE_X> &roomPath)
{
    m_Rooms.clear();

    const Vector2i startRoom{utils::Random(0, MAX_ROOM_SIZE_X-1), 0};
    roomPath[startRoom.y][startRoom.x] = 9; // enter
    Vector2i currentRoom{startRoom};
    Vector2i prevRoom{currentRoom};

    
    bool isGeneratingPath{true};
    while (isGeneratingPath)
    {
        bool foundValidDirection = false;
        Vector2i randomDirection;
        while (!foundValidDirection)
        {
            const int random = utils::Random(1, 9);
            std::cout << random << " ";

            if (random >= 1 && random <= 3) randomDirection = Vector2i{-1, 0};
            else if (random >= 4 && random <= 6) randomDirection = Vector2i{1, 0};
            else randomDirection = Vector2i{0, 1};

            Vector2i newRoom{currentRoom + randomDirection};
            //TODO: Hack should fix
            if((newRoom.x <= 0 || newRoom.x >= MAX_ROOM_SIZE_X-1) && randomDirection.y == 0)
            {
                newRoom = currentRoom - randomDirection;
            }
            
            if (newRoom.x > -1 && newRoom.x < MAX_ROOM_SIZE_X)
            {
                currentRoom = newRoom;
                foundValidDirection = true;
            }
        }

		std::cout << currentRoom << '\n';


        if (randomDirection.y > 0)
        {
            if (currentRoom.y >= MAX_ROOM_SIZE_Y)
            {
                roomPath[currentRoom.y - 1][currentRoom.x] = 8;
                isGeneratingPath = false;
            }
            else
            {
                roomPath[currentRoom.y][currentRoom.x] = 3;
                roomPath[prevRoom.y][prevRoom.x] = 2;
            }
        }
        else
        {
            roomPath[currentRoom.y][currentRoom.x] = 1;
        }

        prevRoom = currentRoom;
    }
    std::cout << '\n';

    roomPath[startRoom.y][startRoom.x] = 9; // enter


    for (int x{}; x < 4; ++x)
    {
        for (int y{}; y < 4; ++y)
        {
            std::cout << roomPath[x][y];
        }
        std::cout << std::endl;
    }
    
    // std::cout << roomPath;

    //m_Rooms.push_back(new Room{RoomDirection{false, false, false, false}, Vector2f{10,10}});
}

int Cave::GetRoomIndex(Vector2i v) const
{
    if (v.x <= 0 || v.y <= 0) return -1;
    if (v.x > 4 || v.y > 4) return -1;

    return v.y * MAX_ROOM_SIZE_X + v.x;
}

void Cave::CreateRoom()
{
	for (int i{}; i < static_cast<int>(m_Rooms.size()); ++i)
	{
		delete m_Rooms[i];
	}
    m_Rooms.clear();
    std::array<std::array<int,MAX_ROOM_SIZE_Y>, MAX_ROOM_SIZE_X> roomPath = {0};

    GenerateRoomTemplate(roomPath);

    for (int x{}; x < MAX_ROOM_SIZE_X; ++x)
    {
        for (int y{}; y < MAX_ROOM_SIZE_Y; ++y)
        {
            RoomDirection roomDir;
            SpecialRoomConditions conditions{SpecialRoomConditions::none};
            switch (roomPath[y][x])
            {
            case 0:
                break;
            case 1:
                roomDir.isLeftOpen = true;
                roomDir.isRightOpen = true;
                break;
            case 2:
                roomDir.isLeftOpen = true;
                roomDir.isRightOpen = true;
                roomDir.isDownOpen = true;
                break;
            case 3:
                roomDir.isLeftOpen = true;
                roomDir.isRightOpen = true;
                roomDir.isTopOpen = true;
                break;
            case 8:
                roomDir.isLeftOpen = true;
                roomDir.isRightOpen = true;
                conditions = SpecialRoomConditions::entrance;
                break;
            case 9:
                roomDir.isLeftOpen = true;
                roomDir.isRightOpen = true;
                roomDir.isTopOpen = true;
                conditions = SpecialRoomConditions::escape;
                break;
            default:
                throw;
            }
            m_Rooms.push_back(new Room{roomDir, Vector2i{100+x*50,100+y*50}, conditions});
        }
    }

    
}
