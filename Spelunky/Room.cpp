#include "pch.h"
#include "Room.h"

#include "SpriteSheetManager.h"
#include "Texture.h"
#include "utils.h"
#include "Vector2i.h"

RoomDirection Room::IsOpen() const
{
	return m_OpenDirection;
}

Room::Room(const RoomDirection& dir, const Vector2i& location, const SpecialRoomConditions special, SpriteSheetManager* spriteSheetManager):
	m_OpenDirection(dir), m_RoomLocation(location),
	m_Conditions(special), m_SpriteSheetManager(spriteSheetManager)
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
		if(m_OpenDirection.isDownOpen == false && m_OpenDirection.isLeftOpen == false && m_OpenDirection.isRightOpen == false && m_OpenDirection.isLeftOpen == false)
		{
			utils::SetColor(Color4f{0,0,0,1});
		}
	}
	utils::FillRect(m_RoomLocation.x - 15, m_RoomLocation.y - 15, 30, 30);
	if(m_OpenDirection.isDownOpen)
	{
		utils::DrawLine(m_RoomLocation.x, m_RoomLocation.y, m_RoomLocation.x, m_RoomLocation.y + 50);
	}
	if(m_OpenDirection.isLeftOpen)
	{
		utils::DrawLine(m_RoomLocation.x, m_RoomLocation.y, m_RoomLocation.x + 50, m_RoomLocation.y);
	}
	if(m_OpenDirection.isTopOpen)
	{
		utils::DrawLine(m_RoomLocation.x, m_RoomLocation.y, m_RoomLocation.x, m_RoomLocation.y - 50);
	}
	if(m_OpenDirection.isRightOpen)
	{
		utils::DrawLine(m_RoomLocation.x, m_RoomLocation.y, m_RoomLocation.x - 50, m_RoomLocation.y);
	}
}

void Room::Draw() const
{
	glPushMatrix();
	glTranslatef(static_cast<float>(m_RoomLocation.x), static_cast<float>(m_RoomLocation.y), 0);

	for (int i{}; i < m_Level.size(); ++i)
	{
		switch (m_Level[i])
		{
		case '0':
			break;
		case '1':
			m_SpriteSheetManager->DrawTile(Vector2f{float((i%10)*64), float((i/10)*64)}, 0, 1);
			break;
		}
	}
	glPopMatrix();
}
