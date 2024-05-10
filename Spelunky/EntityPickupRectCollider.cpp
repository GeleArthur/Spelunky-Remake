#include "pch.h"
#include "EntityPickupRectCollider.h"

EntityPickupRectCollider::EntityPickupRectCollider(const Rectf& collider, const float mass, const float bounciness, WorldManager* worldManager):
    EntityRectCollider(collider, mass, bounciness, worldManager)
{
}

void EntityPickupRectCollider::Update(const float elapsedTime)
{
    if(m_IsPickedUp == true)
    {
        SetVelocity((m_TargetPosition - GetCenter()) );
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
    m_IsPickedUp = false;

    SetVelocity(force);
}

bool EntityPickupRectCollider::TryToPickUp(Entity* pickedUpBy)
{
    if(CanBePickedUp())
    {
        m_PickedUpBy = pickedUpBy;
        m_IsPickedUp = true;
        
        return true;
    }
    return false;
}

void EntityPickupRectCollider::SetTargetPosition(const Vector2f& position)
{
    m_TargetPosition = position;
}

bool EntityPickupRectCollider::GetIsPickedUp() const
{
    return m_IsPickedUp;
}
