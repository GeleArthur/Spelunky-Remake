#include "pch.h"
#include "Cave.h"

#include <array>
#include <iostream>

#include "SpriteSheetManager.h"
#include "utils.h"
#include "Vector2i.h"

// Each Cave or gird of rooms. Is 4x4

Cave::Cave()
{
    std::array<std::array<TileTypes, MAX_CAVE_TILE_COUNT_Y>, MAX_CAVE_TILE_COUNT_X> tiles;
    GenerateCave(tiles);

    int variantIndexes[] = {0,1,4, 5};
    
    for (int x{}; x < MAX_CAVE_TILE_COUNT_X; ++x)
    {
        for (int y{}; y < MAX_CAVE_TILE_COUNT_Y; ++y)
        {
            m_Tiles[x][y] = Tile{tiles[x][y], Vector2i{x,y}, SpriteSheetManager::GetSingleton()};
            if(tiles[x][y] == TileTypes::ground)
            {
                m_Tiles[x][y].SetVariantIndex(variantIndexes[utils::Random(0,3)]);
            }
        }
    }
}

Cave::~Cave()
{
}

void Cave::Draw() const
{
    for (int x{}; x < MAX_CAVE_TILE_COUNT_X; ++x)
    {
        for (int y{}; y < MAX_CAVE_TILE_COUNT_Y; ++y)
        {
            // m_Tiles[x][y].Draw();
            m_Tiles[x][y].Draw();
        }
    }
}

// My guess right now
// 1 = left, right open
// 2 = left, right, bottom
// 3 = left, right, top

void Cave::GenerateCave(std::array<std::array<TileTypes,MAX_CAVE_TILE_COUNT_Y>, MAX_CAVE_TILE_COUNT_X> &tileTypes)
{
    std::array<std::array<PathTypes, MAX_ROOMS_Y>, MAX_ROOMS_X> path{};
    GeneratePath(path);

    for (int x{}; x < tileTypes.size(); ++x)
    {
        for (int y{}; y < tileTypes[x].size(); ++y)
        {
            tileTypes[x][y] = TileTypes::ground;
        }
    }
}

void Cave::GeneratePath(std::array<std::array<PathTypes, MAX_ROOMS_X>, MAX_ROOMS_Y> &roomPath)
{
    const Vector2i startRoom{utils::Random(0, MAX_ROOMS_X-1), 0};
    roomPath[startRoom.y][startRoom.x] = PathTypes::entrance; // enter
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
            if((newRoom.x <= 0 || newRoom.x >= MAX_ROOMS_X-1) && randomDirection.y == 0)
            {
                newRoom = currentRoom - randomDirection;
            }
            
            if (newRoom.x > -1 && newRoom.x < MAX_ROOMS_X)
            {
                currentRoom = newRoom;
                foundValidDirection = true;
            }
        }

        std::cout << currentRoom << '\n';

        // If we went down
        if (randomDirection.y > 0)
        {
            // Did we hit exit?
            if (currentRoom.y >= MAX_ROOMS_Y)
            {
                roomPath[currentRoom.y - 1][currentRoom.x] = PathTypes::exit;
                isGeneratingPath = false;
            }
            else
            {
                // Open the path up
                roomPath[currentRoom.y][currentRoom.x] = PathTypes::leftRightUp;
                if(roomPath[prevRoom.y][prevRoom.x] == PathTypes::leftRightDown)
                    roomPath[prevRoom.y][prevRoom.x] = PathTypes::allOpen;
                else
                    roomPath[prevRoom.y][prevRoom.x] = PathTypes::leftRightDown;
            }
        }
        else // We went left right
        {
            roomPath[currentRoom.y][currentRoom.x] = PathTypes::leftRight;
        }

        prevRoom = currentRoom;
    }
    std::cout << '\n';

    // Make sure entrance 
    roomPath[startRoom.y][startRoom.x] = PathTypes::entrance; // enter


    for (int x{}; x < 4; ++x)
    {
        for (int y{}; y < 4; ++y)
        {
            std::cout << static_cast<int>(roomPath[x][y]);
        }
        std::cout << std::endl;
    }
}
