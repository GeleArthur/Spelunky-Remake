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

    GizmosDrawer::DrawQText(GetCenter() - Vector2f{0, 50}, GetVelocity().ToString());
}

void Rock::DrawPickedUp() const
{
    m_SpriteSheetManager->GetItemsTexture()->Draw(
        GetCenter() - Vector2f{40, 40},
        Rectf{1360, 0, 80,80}
    );
}

bool Rock::CanBePickedUp() const
{
    return IsOnGround();
}

void Rock::CallBackHitEntity(std::vector<std::pair<RayVsRectInfo, EntityRectCollider*>>& hitInfo)
{
    if(!IsOnGround() && !IsPickedUp() && GetVelocity().SquaredLength() > 1000*1000 )
    {
        for (int i{}; i < hitInfo.size(); ++i)
        {
            hitInfo[i].second->YouGotHit(1, GetVelocity());
        }
    }
}
