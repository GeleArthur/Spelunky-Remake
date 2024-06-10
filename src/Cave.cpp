
#include "Cave.h"

#include <array>
#include <iomanip>
#include <iostream>
#include "Game.h"
#include "magic_enum.hpp"
#include "RoomTemplates.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Tile.h"
#include "TileTypes.h"
#include "utils.h"
#include "Vector2i.h"
#include "WorldManager.h"

// Each Cave or gird of rooms. Is 4x4
Cave::Cave(WorldManager* worldManager):
    m_SpriteSheetManager(worldManager->GetSpriteSheet()),
    m_Tiles(CAVE_TILE_COUNT_X),
    m_PathDebug()
{
    for (int x{}; x < CAVE_TILE_COUNT_X; ++x)
    {
        m_Tiles[x].reserve(CAVE_TILE_COUNT_Y);
        
        for (int y{}; y < CAVE_TILE_COUNT_Y; ++y)
        {
            m_Tiles[x].push_back(new Tile{TileTypes::border, Vector2i{x,y}, worldManager});
            
            m_Tiles[x][y]->SetVariantIndex(x%2 + 2*(y%2));
        }
    }
    
    worldManager->SetCave(this);
}
Cave::~Cave()
{
    for (int x = 0; x < m_Tiles.size(); ++x)
    {
        for (int y = 0; y < m_Tiles[x].size(); ++y)
        {
            delete m_Tiles[x][y];
        }
    }
    m_Tiles.clear();
}

void Cave::GenerateLevel()
{
    std::array<std::array<TileTypes, CAVE_GENERATOR_TILE_COUNT_Y>, CAVE_GENERATOR_TILE_COUNT_X> tileTypes;
    GenerateTiles(tileTypes);
    
    const int variantIndexes[] = {0, 1, 4, 5};
    for (int x{}; x < CAVE_GENERATOR_TILE_COUNT_X; ++x)
    {
        for (int y{}; y < CAVE_GENERATOR_TILE_COUNT_Y; ++y)
        {
            const int xWithBorder = x + TILES_BORDER_X;
            const int yWithBorder = y + TILES_BORDER_Y;
            
            m_Tiles[xWithBorder][yWithBorder]->SetTileType(tileTypes[x][y]);

            switch (tileTypes[x][y])
            {
            case TileTypes::ground:
                m_Tiles[xWithBorder][yWithBorder]->SetVariantIndex(variantIndexes[utils::Random(0, 3)]);
                break;
            case TileTypes::spikes:
                m_Tiles[xWithBorder][yWithBorder]->SetVariantIndex(utils::Random(0, 2));
                break;
            case TileTypes::entrance:
                m_EntranceLocation = Vector2f{float(xWithBorder) * Game::TILE_SIZE, float(yWithBorder) * Game::TILE_SIZE};
                break;
            case TileTypes::exit:
                m_ExitLocation = Vector2f{float(xWithBorder) * Game::TILE_SIZE, float(yWithBorder) * Game::TILE_SIZE};
                break;
            default:
                break;
            }
        }
    }
    // m_Tiles[0][0] = Tile{TileTypes::air, Vector2i{0, 0}, SpriteSheetManager::GetSingleton()};
}

void Cave::Draw() const
{
    const Texture* doors = m_SpriteSheetManager->GetDoorsTexture();
    doors->Draw(m_EntranceLocation - Vector2f{128-32, 100}, Rectf{256,0,256,256});
    doors->Draw(m_ExitLocation - Vector2f{128-32, 100}, Rectf{0,0,256,256});
    
    for (int x{}; x < CAVE_TILE_COUNT_X; ++x)
    {
        for (int y{}; y < CAVE_TILE_COUNT_Y; ++y)
        {
            m_Tiles[x][y]->Draw();
        }
    }
    
    
    /*for (int i{}; i < m_PathDebug.size(); ++i)
    {
        for (int j{}; j < m_PathDebug[i].size(); ++j)
        {
            if (m_InfoDebug.entranceLocation == Vector2i{i, j})
            {
                utils::SetColor(Color4f{0, 1, 0, 0.4f}); // GREEN
            }
            else if (m_InfoDebug.exitLocation == Vector2i{i, j})
            {
                utils::SetColor(Color4f{1, 0, 0, 0.4f}); // RED
            }
            else
            {
                switch (m_PathDebug[i][j])
                {
                case PathTypes::sideRoom:
                    utils::SetColor(Color4f{1, 1, 1, 0.4f}); // WHITE
                    break;
                case PathTypes::leftRight:
                    utils::SetColor(Color4f{0, 1, 1, 0.4f}); // CYAN
                    break;
                case PathTypes::bottom:
                    utils::SetColor(Color4f{1, 1, 0, 0.4f}); // YELLOW
                    break;
                case PathTypes::top:
                    utils::SetColor(Color4f{1, 0, 1, 0.4f}); // PINK
                    break;
                }
            }
            utils::FillRect(i * TILES_PER_ROOM_X * 64, j * TILES_PER_ROOM_Y * 64, TILES_PER_ROOM_X * 64,
                            TILES_PER_ROOM_Y * 64);
        }
    }*/
}

void Cave::GenerateTiles(std::array<std::array<TileTypes, CAVE_GENERATOR_TILE_COUNT_Y>, CAVE_GENERATOR_TILE_COUNT_X>& tileArray)
{
    m_EntranceLocation = Vector2f{-1,-1};
    m_ExitLocation = Vector2f{-1,-1};
    
    ExtraPathInformation extra;
    std::array<std::array<PathTypes, MAX_ROOMS_Y>, MAX_ROOMS_X> path{};
    GeneratePath(path, extra);
    m_PathDebug = path;
    m_InfoDebug = extra;
    
    for (int x{}; x < static_cast<int>(path.size()); ++x)
    {
        for (int y{}; y < static_cast<int>(path[x].size()); ++y)
        {
            const std::string* roomString = nullptr;

            if (extra.entranceLocation == Vector2i{x, y})
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
            else if (extra.exitLocation == Vector2i{x, y})
            {
                std::cout << "Exit is: " << magic_enum::enum_name(path[x][y]) << '\n';
                roomString = RoomTemplates::GetRandomString(RoomTemplates::EXIT);
            }
            else
            {
                const PathTypes roomAbove = y > 0 ? path[x][y - 1] : PathTypes::sideRoom;
                
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
                    if (roomAbove == PathTypes::bottom)
                    {
                        roomString = RoomTemplates::GetRandomString(RoomTemplates::BOTTOM_TOP_OPEN);
                    }
                    else
                    {
                        if (utils::Random(0, 1) == 1)
                            roomString = RoomTemplates::GetRandomString(RoomTemplates::BOTTOM_TOP_OPEN);
                        else
                            roomString = RoomTemplates::GetRandomString(RoomTemplates::BOTTOM_OPEN);
                    }
                    break;
                }
            }

            RoomStringToTileType(roomString, tileArray, Vector2i{x, y});
        }
    }
}

void Cave::GeneratePath(std::array<std::array<PathTypes, MAX_ROOMS_X>, MAX_ROOMS_Y>& roomPath,
                        ExtraPathInformation& extraInfo)
{
    const Vector2i startRoom{utils::Random(0, MAX_ROOMS_X - 1), 0};
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
        if (newRoom.x < 0 || newRoom.x > MAX_ROOMS_X - 1)
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
            if (roomPath[currentRoom.x][currentRoom.y] != PathTypes::top)
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
            std::cout << std::setw(12) << magic_enum::enum_name(roomPath[y][x]) << " ";
        }
        std::cout << std::endl;
    }
}

void Cave::RoomStringToTileType(
    const std::string* roomString,
    std::array<std::array<TileTypes, CAVE_GENERATOR_TILE_COUNT_Y>, CAVE_GENERATOR_TILE_COUNT_X>& tileTypes,
    const Vector2i roomLocation)
{
    if (roomString == nullptr)
    {
        std::cout << "Something bad happened but will continue" << std::endl;
        return;
    }

    const std::string processedString = RoomStringPreprocessor(*roomString);

    for (int i{}; i < processedString.size(); ++i)
    {
        const int xLocation = (roomLocation.x * 10) + i % 10;
        const int yLocation = (roomLocation.y * 8) + i / 10;
        TileTypes tileType;
        
        switch (processedString.at(i))
        {
        case '0':
            tileType = TileTypes::air;
            break;
        case '1':
            tileType = TileTypes::ground;
            break;
        case '2':
            if(utils::Random(1,2) == 1)
                tileType = TileTypes::ground;
            else
                tileType = TileTypes::air;
            break;
        case 'P':
            tileType = TileTypes::ladderTop;
            break;
        case 'L':
            tileType = TileTypes::ladder;
            break;
        case '7':
            tileType = TileTypes::spikes;
            break;
        case '4':
            tileType = TileTypes::pushBlock;
            break;
        case '9':
            if(roomLocation.y < 1)
            {
                tileType = TileTypes::entrance;
            }
            else
                tileType = TileTypes::exit;
            break;
            
        default:
            tileType = TileTypes::unknown;
            break;
        }
        tileTypes[xLocation][yLocation] = tileType;
    }
}

// TODO: sucks need something better
std::string Cave::RoomStringPreprocessor(std::string strCopy)
{
    for (int i{}; i < int(strCopy.size()); ++i)
    {
        std::string strObs1 = "00000";
        std::string strObs2 = "00000";
        std::string strObs3 = "00000";
        
        if(strCopy.at(i) == '8')
        {
            switch (utils::Random(1,8))
            {
                case 1: { strObs1 = "00900"; strObs2 = "01110"; strObs3 = "11111"; break; }
                case 2: { strObs1 = "00900"; strObs2 = "02120"; strObs3 = "02120"; break; }
                case 3: { strObs1 = "00000"; strObs2 = "00000"; strObs3 = "92222"; break; }
                case 4: { strObs1 = "00000"; strObs2 = "00000"; strObs3 = "22229"; break; }
                case 5: { strObs1 = "00000"; strObs2 = "11001"; strObs3 = "19001"; break; }
                case 6: { strObs1 = "00000"; strObs2 = "10011"; strObs3 = "10091"; break; }
                case 7: { strObs1 = "11111"; strObs2 = "10001"; strObs3 = "40094"; break; }
                case 8: { strObs1 = "00000"; strObs2 = "12021"; strObs3 = "12921"; break; }
            default:
                throw;
            }
        }
        else if (strCopy.at(i) == '5')
        {
            switch(utils::Random(1,16))
            {
                case 1: { strObs1 = "11111"; strObs2 = "00000"; strObs3 = "00000"; break; }
                case 2: { strObs1 = "00000"; strObs2 = "11110"; strObs3 = "00000"; break; }
                case 3: { strObs1 = "00000"; strObs2 = "01111"; strObs3 = "00000"; break; }
                case 4: { strObs1 = "00000"; strObs2 = "00000"; strObs3 = "11111"; break; }
                case 5: { strObs1 = "00000"; strObs2 = "20200"; strObs3 = "17177"; break; }
                case 6: { strObs1 = "00000"; strObs2 = "02020"; strObs3 = "71717"; break; }
                case 7: { strObs1 = "00000"; strObs2 = "00202"; strObs3 = "77171"; break; }
                case 8: { strObs1 = "00000"; strObs2 = "22200"; strObs3 = "11100"; break; }
                case 9: { strObs1 = "00000"; strObs2 = "02220"; strObs3 = "01110"; break; }
                case 10: { strObs1 = "00000"; strObs2 = "00222"; strObs3 = "00111"; break; }
                case 11: { strObs1 = "11100"; strObs2 = "22200"; strObs3 = "00000"; break; }
                case 12: { strObs1 = "01110"; strObs2 = "02220"; strObs3 = "00000"; break; }
                case 13: { strObs1 = "00111"; strObs2 = "00222"; strObs3 = "00000"; break; }
                case 14: { strObs1 = "00000"; strObs2 = "02220"; strObs3 = "21112"; break; }
                case 15: { strObs1 = "00000"; strObs2 = "20100"; strObs3 = "77117"; break; }
                case 16: { strObs1 = "00000"; strObs2 = "00102"; strObs3 = "71177"; break; }
            default:
                throw;
            }
        }
        else if(strCopy.at(i) == '6')
        {
            switch(utils::Random(1,10))
            {
                case 1: { strObs1 = "11111"; strObs2 = "00000"; strObs3 = "00000"; break; }
                case 2: { strObs1 = "22222"; strObs2 = "00000"; strObs3 = "00000"; break; }
                case 3: { strObs1 = "11100"; strObs2 = "22200"; strObs3 = "00000"; break; }
                case 4: { strObs1 = "01110"; strObs2 = "02220"; strObs3 = "00000"; break; }
                case 5: { strObs1 = "00111"; strObs2 = "00222"; strObs3 = "00000"; break; }
                case 6: { strObs1 = "00000"; strObs2 = "01110"; strObs3 = "00000"; break; }
                case 7: { strObs1 = "00000"; strObs2 = "01110"; strObs3 = "02220"; break; }
                case 8: { strObs1 = "00000"; strObs2 = "02220"; strObs3 = "01110"; break; }
                case 9: { strObs1 = "00000"; strObs2 = "00220"; strObs3 = "01111"; break; }
                case 10: { strObs1 = "00000"; strObs2 = "22200"; strObs3 = "11100"; break; }
            default:
                throw;
            }
        }

        if(strCopy.at(i) == '6' || strCopy.at(i) == '5' || strCopy.at(i) == '8')
        {
            strCopy.replace(i, 5, strObs1);
            strCopy.replace(i+10, 5, strObs2);
            strCopy.replace(i+20, 5, strObs3);
        }
        
    }
    
    return strCopy;
}

Vector2f Cave::GetEntrance() const
{
    return m_EntranceLocation;
}

Vector2f Cave::GetExit() const
{
    return m_ExitLocation;
}

const std::vector<std::vector<Tile*>>& Cave::GetTiles() const
{
    return m_Tiles;
}

const Tile& Cave::GetTile(const int x, const int y) const
{
    return *m_Tiles.at(x).at(y);
}

const Tile& Cave::GetTile(const Vector2i& location) const
{
    return *m_Tiles.at(location.x).at(location.y);
}

void Cave::ExplodeTile(const Vector2i& tileIndex) const
{
    if(tileIndex.x < 0 || tileIndex.x > CAVE_TILE_COUNT_X ||
    tileIndex.y < 0 || tileIndex.y > CAVE_TILE_COUNT_Y) return;
    
    Tile* tile = m_Tiles.at(tileIndex.x).at(tileIndex.y);
    const TileTypes tileType = tile->GetTileType();
    if(tileType != TileTypes::border && tileType != TileTypes::exit && tileType != TileTypes::entrance)
    {
        tile->SetTileType(TileTypes::air);
    }
}
