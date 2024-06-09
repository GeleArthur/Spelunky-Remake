#include "pch.h"
#include "Rock.h"

#include "GizmosDrawer.h"
#include "RectPhysicsCollider.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "utils.h"
#include "WorldManager.h"

Rock::Rock(const Vector2f& position, WorldManager* worldManager):
    EntityPickupRectCollider(Rectf{position.x, position.y, 34, 34}, 999, 3, 0.3f, true, worldManager),
    m_SpriteSheetManager(worldManager->GetSpriteSheet())
{
}

EntityType Rock::GetEntityType() const
{
    return EntityType::rock;
}

void Rock::Draw() const
{
    m_SpriteSheetManager->GetItemsTexture()->Draw(
        GetCenter() - Vector2f{40, 40},
        Rectf{1360, 0, 80,80}
    );
}
void Rock::Update(const float elapsedTime)
{
    if(IsDead()) return;
    
    if(IsOnGround())
    {
        const Vector2f& velocity = m_PhysicsCollider.GetVelocity();
        Vector2f newVelocity{
            std::max(std::abs(velocity.x) * m_FrictionOnFloor - 0.2f, 0.0f) * (velocity.x >= 0 ? 1.0f : -1.0f),
            std::max(std::abs(velocity.y) * m_FrictionOnFloor - 0.2f, 0.0f) * (velocity.y >= 0 ? 1.0f : -1.0f)
        };
        
        m_PhysicsCollider.SetVelocity(newVelocity);
    }

    if(IsDead()) return;
    
    EntityPickupRectCollider::Update(elapsedTime);
}

