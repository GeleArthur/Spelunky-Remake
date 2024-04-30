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
    RectPhysicsCollider(Rectf{position.x, position.y, 40, 40}, 3, 0.8f, worldManager),
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
    UpdatePhysics(elapsedTime);
}

void Rock::Draw() const
{
    // GetCollider()->DebugDraw();
    m_SpriteSheetManager->GetItemsTexture()->Draw(
        GetCenter() - Vector2f{40, 40},
        Rectf{1360, 0, 80,80}
    );
}

bool Rock::CanBePickedUp()
{
    return false;
}


