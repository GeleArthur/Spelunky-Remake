#include "pch.h"
#include "Cave.h"

#include <array>
#include <iostream>

#include "RoomTemplates.h"
#include "SpriteSheetManager.h"
#include "Tile.h"
#include "TileTypes.h"
#include "utils.h"
#include "Vector2i.h"

// Each Cave or gird of rooms. Is 4x4

Cave::Cave(): m_Tiles(MAX_CAVE_TILE_COUNT_X), m_PathDebug()
{
    for (int x{}; x < MAX_CAVE_TILE_COUNT_X; ++x)
    {
        m_Tiles[x].reserve(MAX_CAVE_TILE_COUNT_Y);
    }
    
    std::array<std::array<TileTypes, MAX_CAVE_TILE_COUNT_Y>, MAX_CAVE_TILE_COUNT_X> tileTypes;
    GenerateTiles(tileTypes);

    const int variantIndexes[] = {0,1,4,5};
    
    for (int x{}; x < MAX_CAVE_TILE_COUNT_X; ++x)
    {
        for (int y{}; y < MAX_CAVE_TILE_COUNT_Y; ++y)
        {
            m_Tiles[x].emplace_back(Tile{tileTypes[x][y], Vector2i{x,y}, SpriteSheetManager::GetSingleton()});
            if(tileTypes[x][y] == TileTypes::ground)
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

    for (int i{}; i < m_PathDebug.size(); ++i)
    {
        for (int j{}; j < m_PathDebug[i].size(); ++j)
        {
            switch (m_PathDebug[i][j])
            {
            case PathTypes::closed:
                utils::SetColor(Color4f{1,1,1,0.4});
                break;
            case PathTypes::leftRight:
                utils::SetColor(Color4f{0,0,1,0.4});
                break;
            case PathTypes::leftRightUp:
                utils::SetColor(Color4f{1,0,1,0.4});
                break;
            case PathTypes::leftRightDown:
                utils::SetColor(Color4f{0,1,1,0.4});
                break;
            case PathTypes::allOpen:
                utils::SetColor(Color4f{1,1,0,0.4});
                break;
            case PathTypes::entrance:
                utils::SetColor(Color4f{0,1,0,0.4});
                break;
            case PathTypes::exit:
                utils::SetColor(Color4f{1,0,0,0.4});
                break;
            }
            utils::FillRect(i*TILES_PER_ROOM_X*64, j*TILES_PER_ROOM_Y*64, TILES_PER_ROOM_X*64 , TILES_PER_ROOM_Y*64);
        }
    }
}

// My guess right now
// 1 = left, right open
// 2 = left, right, bottom
// 3 = left, right, top

void Cave::GenerateTiles(std::array<std::array<TileTypes,MAX_CAVE_TILE_COUNT_Y>, MAX_CAVE_TILE_COUNT_X> &tileArray)
{
    std::array<std::array<PathTypes, MAX_ROOMS_Y>, MAX_ROOMS_X> path{};
    GeneratePath(path);
    m_PathDebug = path;
    
    for (int x{}; x < static_cast<int>(path.size()); ++x)
    {
        for (int y{}; y < static_cast<int>(path[x].size()); ++y)
        {
            switch (path[x][y])
            {
            case PathTypes::closed:
                RoomStringToTileType(RoomTemplates::SIDE_ROOMS[utils::Random(0, int(RoomTemplates::SIDE_ROOMS.size()-1))], tileArray, Vector2i{x,y});
                break;
            case PathTypes::leftRight:
                RoomStringToTileType(RoomTemplates::LEFT_RIGHT[utils::Random(0, int(RoomTemplates::LEFT_RIGHT.size()-1))], tileArray, Vector2i{x,y});
                break;
            case PathTypes::leftRightUp:
                RoomStringToTileType(RoomTemplates::LEFT_RIGHT[utils::Random(0, int(RoomTemplates::LEFT_RIGHT.size()-1))], tileArray, Vector2i{x,y});
                break;
            case PathTypes::leftRightDown:
                
                break;
            case PathTypes::allOpen:
                
                break;
            case PathTypes::entrance:
                RoomStringToTileType(RoomTemplates::ENTRANCE_LEFT_RIGHT[utils::Random(0, int(RoomTemplates::ENTRANCE_LEFT_RIGHT.size()-1))], tileArray, Vector2i{x,y});
                break;
            case PathTypes::exit:
                RoomStringToTileType(RoomTemplates::EXIT[utils::Random(0, int(RoomTemplates::EXIT.size()-1))], tileArray, Vector2i{x,y});
                break;
            }
        }
    }
}

void Cave::GeneratePath(std::array<std::array<PathTypes, MAX_ROOMS_X>, MAX_ROOMS_Y> &roomPath)
{
    const Vector2i startRoom{utils::Random(0, MAX_ROOMS_X-1), 0};
    roomPath[startRoom.x][startRoom.y] = PathTypes::entrance; // enter
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
                roomPath[currentRoom.x][currentRoom.y-1] = PathTypes::exit;
                isGeneratingPath = false;
            }
            else
            {
                // Open the path up
                roomPath[currentRoom.x][currentRoom.y] = PathTypes::leftRightUp;
                if(roomPath[prevRoom.x][prevRoom.y] == PathTypes::leftRightDown)
                    roomPath[prevRoom.x][prevRoom.y] = PathTypes::allOpen;
                else
                    roomPath[prevRoom.x][prevRoom.y] = PathTypes::leftRightDown;
            }
        }
        else // We went left right
        {
            roomPath[currentRoom.x][currentRoom.y] = PathTypes::leftRight;
        }

        prevRoom = currentRoom;
    }
    std::cout << '\n';

    // Make sure entrance 
    roomPath[startRoom.x][startRoom.y] = PathTypes::entrance; // enter


    for (int x{}; x < 4; ++x)
    {
        for (int y{}; y < 4; ++y)
        {
            std::cout << static_cast<int>(roomPath[y][x]);
        }
        std::cout << std::endl;
    }
}

void Cave::RoomStringToTileType(
    const std::string& roomString,
    std::array<std::array<TileTypes, MAX_CAVE_TILE_COUNT_Y>,MAX_CAVE_TILE_COUNT_X> &tileTypes,
    Vector2i roomLocation)
{
    for (int i{}; i < roomString.size(); ++i)
    {
        int xLocation = (roomLocation.x * 10) + i%10;
        int yLocation = (roomLocation.y *8) + i/10;
        TileTypes tileType;
        
        switch (roomString[i])
        {
            case '0':
                tileType = TileTypes::air;
                break;
            case '1':
                tileType = TileTypes::ground;
                break;
            default:
                tileType = TileTypes::unknown;
                break;
        }
        tileTypes[xLocation][yLocation] = tileType;
    }
}
