#include "pch.h"
#include "Rock.h"

#include "GizmosDrawer.h"
#include "RectPhysicsCollider.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "utils.h"
#include "WorldManager.h"

Rock::Rock(const Vector2f& position, WorldManager* worldManager):
    EntityPickupRectCollider(Rectf{position.x, position.y, 34, 34}, 999, 3, 0.3f, 0.3f, worldManager),
    m_SpriteSheetManager(worldManager->GetSpriteSheet())
{
}

EntityType Rock::GetEntityType() const
{
    return EntityType::rock;
}

void Rock::Draw() const
{
    if(IsPickedUp() == false)
    {
        DrawPickedUp();
    }
}

void Rock::DrawPickedUp() const
{
    m_SpriteSheetManager->GetItemsTexture()->Draw(
        GetCenter() - Vector2f{40, 40},
        Rectf{1360, 0, 80,80}
    );
}
