#include "pch.h"
#include "Room.h"

#include "utils.h"
#include "Vector2i.h"

RoomDirection Room::IsOpen() const
{
	return m_OpenDirection;
}

Room::Room(const RoomDirection& dir, const Vector2i& location, SpecialRoomConditions special):
	m_OpenDirection(dir), m_RoomLocation(location),
	m_Conditions(special)
{
}

void Room::TestDrawRoom() const
{
	if(m_Conditions == SpecialRoomConditions::entrance)
	{
		utils::SetColor(Color4f{1,0,0,1});
	}
	else if(m_Conditions == SpecialRoomConditions::escape)
	{
		utils::SetColor(Color4f{1,1,0,1});
	}
	else if(m_Conditions == SpecialRoomConditions::none)
	{
		utils::SetColor(Color4f{1,1,1,1});
	}
	utils::DrawPoint(m_RoomLocation.x, m_RoomLocation.y, 30);
	if(!m_OpenDirection.isDownOpen)
	{
		utils::DrawLine(m_RoomLocation.x, m_RoomLocation.y, m_RoomLocation.x + 50, m_RoomLocation.y);
	}
	if(!m_OpenDirection.isLeftOpen)
	{
		utils::DrawLine(m_RoomLocation.x, m_RoomLocation.y, m_RoomLocation.x, m_RoomLocation.y + 50);
	}
	if(!m_OpenDirection.isTopOpen)
	{
		utils::DrawLine(m_RoomLocation.x, m_RoomLocation.y + 50, m_RoomLocation.x + 50, m_RoomLocation.y + 50);
	}
	if(!m_OpenDirection.isRightOpen)
	{
		utils::DrawLine(m_RoomLocation.x + 50, m_RoomLocation.y, m_RoomLocation.x + 50, m_RoomLocation.y + 50);
	}
}
