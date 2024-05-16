#include "pch.h"
#include "EntityPickupRectCollider.h"

#include "GizmosDrawer.h"
#include "Tile.h"

EntityPickupRectCollider::EntityPickupRectCollider(const Rectf& collider, const int health, const float mass, const float bounciness, const float frictionOnGround, WorldManager* worldManager):
    EntityRectCollider(collider, health, mass, bounciness, worldManager),
    m_FrictionOnFloor(frictionOnGround)
{
}

void EntityPickupRectCollider::Update(const float elapsedTime)
{
    if(m_IsOnGround)
    {
        const Vector2f& velocity = GetVelocity();
        Vector2f newVelocity{
            std::max(std::abs(velocity.x) * m_FrictionOnFloor - 0.2f, 0.0f) * (velocity.x >= 0 ? 1.0f : -1.0f),
            std::max(std::abs(velocity.y) * m_FrictionOnFloor - 0.2f, 0.0f) * (velocity.y >= 0 ? 1.0f : -1.0f)
        };
        
        SetVelocity(newVelocity);
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

bool EntityPickupRectCollider::TryToPickUp(EntityRectCollider* pickedUpBy)
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

bool EntityPickupRectCollider::IsPickedUp() const
{
    return m_PickedUpBy != nullptr;
}

bool EntityPickupRectCollider::IsOnGround() const
{
    return m_IsOnGround;
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
