#pragma once
#include <unordered_map>
#include <vector>
#include "PathTypes.h"

//TODO: Move to CAVE
class RoomTemplates final
{
public:
    // static void GetRoom(std::string& out, const std::vector<std::string>& array1, const std::vector<std::string>& array2);
    // static void GetRoom(std::string& out, const std::vector<std::string>& array1);
    
    const static std::vector<std::string> ENTRANCE_LEFT_RIGHT;
    const static std::vector<std::string> ENTRANCE_DOWN;
    const static std::vector<std::string> EXIT;
    const static std::vector<std::string> LEFT_RIGHT;
    const static std::vector<std::string> SIDE_ROOMS;
    const static std::vector<std::string> TOP_OPEN;
    const static std::vector<std::string> BOTTOM_TOP_OPEN;
    const static std::vector<std::string> BOTTOM_OPEN;

    // Special
    const static std::vector<std::string> IDOLS;
    const static std::vector<std::string> ALTARS;
    const static std::unordered_map<PathTypes, std::vector<std::string>> PATH_TO_ROOM;

    const static std::string* GetRandomString(const std::vector<std::string>& strings);
};
