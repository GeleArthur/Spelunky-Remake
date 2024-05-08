#include "pch.h"
#include "Rock.h"

#include "CirclePhysicsCollider.h"
#include "RectPhysicsCollider.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "WorldManager.h"


Rock::Rock(const Vector2f& position, WorldManager* worldManager):
    Entity(),
    PickupItem(),
    RectPhysicsCollider(Rectf{position.x, position.y, 40, 40}, 3, 0.3f, worldManager),
    m_SpriteSheetManager(worldManager->GetSpriteSheet())
{
}

EntityType Rock::GetEntityType() const
{
    return EntityType::rock;
}

bool Rock::Throw(Vector2f force)
{
    return false;
}

void Rock::Update(const float elapsedTime)
{
    if(m_IsPickedUp == false)
    {
        ApplyForce(Vector2f{0,1000} * elapsedTime);
    }
    else
    {
        ApplyForce((m_targetLocation - GetCenter()) );
    }
    UpdatePhysics(elapsedTime);
}

void Rock::Draw() const
{
    // If we are picked up let the player draw me.
    if(m_IsPickedUp == false)
    {
        DrawPickedUp();
    }
}

bool Rock::CanBePickedUp()
{
    return false;
}

void Rock::DrawPickedUp() const
{
    m_SpriteSheetManager->GetItemsTexture()->Draw(
        GetCenter() - Vector2f{40, 40},
        Rectf{1360, 0, 80,80}
    );
}

void Rock::SetTargetPosition(Vector2f position)
{
    m_targetLocation = position;
}


