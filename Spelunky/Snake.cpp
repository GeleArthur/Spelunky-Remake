#include "pch.h"
#include "Snake.h"

#include "Cave.h"
#include "Game.h"
#include "GizmosDrawer.h"

#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Vector2i.h"
#include "WorldManager.h"

Snake::Snake(const Vector2f& position, WorldManager* worldManager) :
    EnemyEntity(Rectf{position.x, position.y, 52, 52}, 1, 1, 0, worldManager),
    m_MovingLeft(rand() % 2 == 0),
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
    m_PhysicsCollider.SetVelocity(m_MovingLeft ? Vector2f{100 , m_PhysicsCollider.GetVelocity().y} : Vector2f{-100, m_PhysicsCollider.GetVelocity().y});
    const Vector2i nextTile = Vector2i((GetCenter() + (m_MovingLeft ? Vector2f{-25, 0}: Vector2f{25, 0}))  / Game::TILE_SIZE) + Vector2i{m_MovingLeft ? 1 : -1, 0};
    const Vector2i nextTileBottom = Vector2i((GetCenter() + Vector2f{0, Game::TILE_SIZE} + (m_MovingLeft ? Vector2f{-25, 0}: Vector2f{25, 0}))  / Game::TILE_SIZE) + Vector2i{m_MovingLeft ? 1 : -1, 0};
    
    const TileTypes InFrontOfMe = m_Cave->GetTile(nextTile).GetTileType();
    const TileTypes UnderMe = m_Cave->GetTile(nextTileBottom).GetTileType();
    if(InFrontOfMe == TileTypes::ground || InFrontOfMe == TileTypes::border || UnderMe == TileTypes::air)
    {
        m_MovingLeft = !m_MovingLeft;
    }
    
    Entity::Update(elapsedTime);
    CheckToHurtPlayer();
}

EntityType Snake::GetEntityType() const
{
    return EntityType::snake;
}
