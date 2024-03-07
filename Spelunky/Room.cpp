#include "pch.h"
#include "Room.h"

#include "utils.h"

RoomDirection Room::IsOpen() const
{
	return m_OpenDirection;
}

Room::Room(const RoomDirection& dir, const Vector2f& location): m_OpenDirection(dir), m_RoomLocation(location)
{
}

void Room::TestDrawRoom() const
{
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
