#include "pch.h"
#include "EntityPickupRectCollider.h"

#include "GizmosDrawer.h"
#include "Tile.h"

EntityPickupRectCollider::EntityPickupRectCollider(const Rectf& collider, const float mass, const float bounciness, const float frictionOnGround, WorldManager* worldManager):
    EntityRectCollider(collider, mass, bounciness, worldManager),
    m_FrictionOnFloor(frictionOnGround)
{
}

void EntityPickupRectCollider::Update(const float elapsedTime)
{
    if(m_IsOnGround)
    {
        SetVelocity((GetVelocity() * m_FrictionOnFloor)-Vector2f{0.2f, 0.2f});
    }
    
    m_IsOnGround = false;
    if(m_PickedUpBy != nullptr)
    {
        SetCenter(m_CenterOfTarget);
        SetVelocity((m_CenterOfTarget - m_GoingToPosition) / elapsedTime );
        UpdatePhysics(elapsedTime);
    }
    else
    {
        EntityRectCollider::Update(elapsedTime);
    }
}

void EntityPickupRectCollider::Throw(const Vector2f& force)
{
    m_PickedUpBy = nullptr;

    SetVelocity(force);
}

bool EntityPickupRectCollider::TryToPickUp(Entity* pickedUpBy)
{
    if(CanBePickedUp())
    {
        m_PickedUpBy = pickedUpBy;
        
        return true;
    }
    return false;
}

void EntityPickupRectCollider::SetTargetPosition(const Vector2f& position, const Vector2f& goingTo)
{
    m_CenterOfTarget = position;
    m_GoingToPosition = goingTo;
}

bool EntityPickupRectCollider::GetIsPickedUp() const
{
    return m_PickedUpBy != nullptr;
}

void EntityPickupRectCollider::CallBackHitTile(std::vector<std::pair<const Tile*, RayVsRectInfo>>& hitInfo)
{
    for (int i{}; i < hitInfo.size(); ++i)
    {
        switch (hitInfo[i].first->GetTileType())
        {
        case TileTypes::ground:
        case TileTypes::border:
            if(hitInfo[i].second.normal.y < 0)
            {
                m_IsOnGround = true;
            }
         break;
        default:
            break;
        }
    }
}
