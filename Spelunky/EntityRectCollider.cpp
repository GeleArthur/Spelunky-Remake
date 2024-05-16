#include "pch.h"
#include "EntityRectCollider.h"

EntityRectCollider::EntityRectCollider(const Rectf& collider, const int health, const float mass, const float bounciness, WorldManager* worldManager):
    RectPhysicsCollider(collider, mass, bounciness, worldManager),
    m_Health(health)
{
}

void EntityRectCollider::Update(const float elapsedTime)
{
    if(IsDead()) return;
    ApplyForce(Vector2f{0,1000} * elapsedTime);
    UpdatePhysics(elapsedTime);
}

void EntityRectCollider::YouGotHit(const int damage, const Vector2f& force)
{
    m_Health -= damage;
    ApplyForce(force);

    // Spawn Blood particle
}

bool EntityRectCollider::IsDead() const
{
    return m_Health <= 0;
}

