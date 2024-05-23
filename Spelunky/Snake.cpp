#include "pch.h"
#include "Snake.h"

#include "Cave.h"
#include "GizmosDrawer.h"
#include "GlobalValues.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Vector2i.h"
#include "WorldManager.h"

Snake::Snake(const Vector2f& position, WorldManager* worldManager) :
    EntityRectCollider(Rectf{position.x, position.y, 52, 52}, 1, 1, 0, worldManager),
    m_SpriteSheetManager(worldManager->GetSpriteSheet()),
    m_Cave(worldManager->GetCave())
{
}

void Snake::Draw() const
{
    if(IsDead()) return;
    glPushMatrix();
    glTranslatef(GetCenter().x, GetCenter().y, 0);
    if(!m_MovingLeft)
    {
        glScalef(-1, 1, 1);
    }
    
    m_SpriteSheetManager->GetMonsterTexture()->Draw(
        Vector2f{-40, -40},
        Rectf{0, 0, 80, 80});
    glPopMatrix();
}

void Snake::Update(const float elapsedTime)
{
    SetVelocity(m_MovingLeft ? Vector2f{100 , GetVelocity().y} : Vector2f{-100, GetVelocity().y});
    const Vector2i nextTile = Vector2i((GetCenter() + (m_MovingLeft ? Vector2f{-25, 0}: Vector2f{25, 0}))  / spelucky_settings::g_TileSize) + Vector2i{m_MovingLeft ? 1 : -1, 0};
    const Vector2i nextTileBottom = Vector2i((GetCenter() + Vector2f{0, spelucky_settings::g_TileSize} + (m_MovingLeft ? Vector2f{-25, 0}: Vector2f{25, 0}))  / spelucky_settings::g_TileSize) + Vector2i{m_MovingLeft ? 1 : -1, 0};
    
    const TileTypes InFrontOfMe = m_Cave->GetTile(nextTile).GetTileType();
    const TileTypes UnderMe = m_Cave->GetTile(nextTileBottom).GetTileType();
    if(InFrontOfMe == TileTypes::ground || InFrontOfMe == TileTypes::border || UnderMe == TileTypes::air)
    {
        m_MovingLeft = !m_MovingLeft;
    }
    
    EntityRectCollider::Update(elapsedTime);
}

EntityType Snake::GetEntityType() const
{
    return EntityType::snake;
}
