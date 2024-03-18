#include "pch.h"
#include "Cave.h"

#include <array>
#include <iomanip>
#include <iostream>

#include "magic_enum.hpp"
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
            m_Tiles[x][y].Draw();
        }
    }

    for (int i{}; i < m_PathDebug.size(); ++i)
    {
        for (int j{}; j < m_PathDebug[i].size(); ++j)
        {
            if(m_InfoDebug.entranceLocation== Vector2i{i,j})
            {
                utils::SetColor(Color4f{0,1,0,0.4f}); // GREEN
            }
            else if(m_InfoDebug.exitLocation== Vector2i{i,j})
            {
                utils::SetColor(Color4f{1,0,0,0.4f}); // RED
            }
            else
            {
                switch (m_PathDebug[i][j])
                {
                case PathTypes::sideRoom:
                    utils::SetColor(Color4f{1,1,1,0.4f}); // WHITE
                    break;
                case PathTypes::leftRight:
                    utils::SetColor(Color4f{0,1,1,0.4f}); // CYAN
                    break;
                case PathTypes::bottom:
                    utils::SetColor(Color4f{1,1,0,0.4f}); // YELLOW
                    break;
                case PathTypes::top:
                    utils::SetColor(Color4f{1,0,1,0.4f}); // PINK
                    break;
                }
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
    ExtraPathInformation extra;
    std::array<std::array<PathTypes, MAX_ROOMS_Y>, MAX_ROOMS_X> path{};
    GeneratePath(path, extra);
    m_PathDebug = path;
    m_InfoDebug = extra;
    
    for (int x{}; x < static_cast<int>(path.size()); ++x)
    {
        for (int y{}; y < static_cast<int>(path[x].size()); ++y)
        {
            PathTypes roomAbove = y > 0? path[x][y-1] : PathTypes::sideRoom;
            const std::string* roomString = nullptr;
            
            if(extra.entranceLocation == Vector2i{x,y})
            {
                std::cout << "Entrance is: " << magic_enum::enum_name(path[x][y]) << '\n';
                switch (path[x][y])
                {
                case PathTypes::leftRight:
                    roomString = RoomTemplates::GetRandomString(RoomTemplates::ENTRANCE_LEFT_RIGHT);
                    break;
                case PathTypes::bottom:
                    roomString = RoomTemplates::GetRandomString(RoomTemplates::ENTRANCE_DOWN);
                    break;
                    default:
                        throw;
                }
            }
            else if(extra.exitLocation == Vector2i{x,y})
            {
                std::cout << "Exit is: " << magic_enum::enum_name(path[x][y]) << '\n';
                roomString = RoomTemplates::GetRandomString(RoomTemplates::EXIT);
            }
            else
            {
                switch (path[x][y])
                {
                case PathTypes::sideRoom:
                    roomString = RoomTemplates::GetRandomString(RoomTemplates::SIDE_ROOMS);
                    //Extra: add idols
                    break;
                case PathTypes::leftRight:
                    roomString = RoomTemplates::GetRandomString(RoomTemplates::LEFT_RIGHT);
                    break;
                case PathTypes::top:
                    roomString = RoomTemplates::GetRandomString(RoomTemplates::TOP_OPEN);
                    break;
                case PathTypes::bottom:
                    if(roomAbove == PathTypes::bottom)
                    {
                        roomString = RoomTemplates::GetRandomString(RoomTemplates::BOTTOM_TOP_OPEN);
                    }
                    else
                    {
                        if(utils::Random(0,1) == 1)
                            roomString = RoomTemplates::GetRandomString(RoomTemplates::BOTTOM_TOP_OPEN);
                        else
                            roomString = RoomTemplates::GetRandomString(RoomTemplates::BOTTOM_OPEN);
                    }
                    break;
                }
            }

            RoomStringToTileType(roomString, tileArray, Vector2i{x,y});
        }
    }
}

void Cave::GeneratePath(std::array<std::array<PathTypes, MAX_ROOMS_X>, MAX_ROOMS_Y> &roomPath, ExtraPathInformation& extraInfo)
{
    const Vector2i startRoom{utils::Random(0, MAX_ROOMS_X-1), 0};
    extraInfo.entranceLocation = startRoom;
    Vector2i currentRoom{startRoom};
    Vector2i prevRoom{currentRoom};

    roomPath[startRoom.x][startRoom.y] = PathTypes::leftRight;
    
    bool isGeneratingPath{true};
    while (isGeneratingPath)
    {
        Vector2i randomDirection;
        const int random = utils::Random(1, 9);
        
        if (random >= 1 && random <= 3) randomDirection = Vector2i{-1, 0};
        else if (random >= 4 && random <= 6) randomDirection = Vector2i{1, 0};
        else randomDirection = Vector2i{0, 1};

        Vector2i newRoom{currentRoom + randomDirection};
        if(newRoom.x < 0 || newRoom.x > MAX_ROOMS_X-1)
        {
            // Flip if we hit a wall
            newRoom = currentRoom - randomDirection;
        }
        
        currentRoom = newRoom;
 

        std::cout << currentRoom << '\n';

        // If we went down
        if (randomDirection.y > 0)
        {
            // Did we hit exit?
            if (currentRoom.y >= MAX_ROOMS_Y)
            {
                extraInfo.exitLocation = prevRoom;
                isGeneratingPath = false;
            }
            else
            {
                // Open the path up
                roomPath[currentRoom.x][currentRoom.y] = PathTypes::top;
                roomPath[prevRoom.x][prevRoom.y] = PathTypes::bottom;
            }
        }
        else // We went left right
        {
            if(roomPath[currentRoom.x][currentRoom.y] != PathTypes::top)
            {
                roomPath[currentRoom.x][currentRoom.y] = PathTypes::leftRight;
            }
        }

        prevRoom = currentRoom;
    }
    std::cout << '\n';

    for (int x{}; x < 4; ++x)
    {
        for (int y{}; y < 4; ++y)
        {
            std::cout <<std::setw(12) << magic_enum::enum_name(roomPath[y][x]) << " ";
        }
        std::cout << std::endl;
    }
}

void Cave::RoomStringToTileType(
    const std::string* roomString,
    std::array<std::array<TileTypes, MAX_CAVE_TILE_COUNT_Y>,MAX_CAVE_TILE_COUNT_X> &tileTypes,
    Vector2i roomLocation)
{
    if(roomString == nullptr)
    {
        std::cout << "Something bad happened but will continue" << std::endl;
        return;
    }
    for (int i{}; i < roomString->size(); ++i)
    {
        int xLocation = (roomLocation.x * 10) + i%10;
        int yLocation = (roomLocation.y *8) + i/10;
        TileTypes tileType;
        
        switch (roomString->at(i))
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
