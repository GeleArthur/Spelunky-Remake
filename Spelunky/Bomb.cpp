#include "pch.h"
#include "Bomb.h"

#include "Cave.h"
#include "GizmosDrawer.h"
#include "GlobalValues.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Vector2i.h"
#include "WorldManager.h"

Bomb::Bomb(const Vector2f& position, WorldManager* worldManager)
    : EntityRectCollider(Rectf{position.x, position.y, 34, 34}, 999, 5, 0.3f, worldManager),
    m_SpriteSheetManager(worldManager->GetSpriteSheet()),
    m_WorldManager{worldManager}
{
}

EntityType Bomb::GetEntityType() const
{
    return EntityType::bomb;
}

void Bomb::Draw() const
{
    if(IsDead()) return;
    glPushMatrix();
    glTranslatef(GetCenter().x, GetCenter().y, 0);

    int bombImage;
    const float invertTimer = m_TimerStart - m_Timer;
    if(m_Timer < 0.2)
    {
        bombImage = 1+static_cast<int>(std::floor(invertTimer*invertTimer*10))%2;

        
    }
    else
    {
        bombImage = static_cast<int>(std::floor(invertTimer*invertTimer*5))%2;
    }
    
    m_SpriteSheetManager->GetItemsTexture()->Draw(
        Vector2f{-40, -40},
        Rectf{(5+bombImage)*80.0f, 3*80, 80,80}
    );

    glPopMatrix();
}

void Bomb::Update(float elapsedTime)
{
    if(IsDead()) return;
    EntityRectCollider::Update(elapsedTime);

    m_Timer -= elapsedTime;

    if(m_Timer < 0)
    {
        Explode();
    }
}

void Bomb::Throw(const Vector2f& position, const Vector2f& velocity)
{
    m_Health = 9999;
    SetCenter(position);
    SetVelocity(velocity);
    m_Timer = m_TimerStart;
}

void Bomb::Explode()
{
    m_Health = 0;

    const Vector2i center = Vector2i{GetCenter() / spelucky_settings::g_TileSize};
    
    for (int x{-m_ExplodeRadius}; x < m_ExplodeRadius; ++x)
    {
        for (int y{-m_ExplodeRadius}; y < m_ExplodeRadius; ++y)
        {
            if(x*x + y*y <= m_ExplodeRadius*m_ExplodeRadius)
            {
                m_WorldManager->GetCave()->ExplodeTile(center + Vector2i{x, y});
            }
        }
    }
}
