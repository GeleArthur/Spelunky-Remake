#include "pch.h"
#include "Entity.h"

Entity::Entity(const Rectf& collider, const int health, const float mass, const float bounciness, WorldManager* worldManager):
    m_Health(health),
    m_PhysicsCollider(collider, mass, bounciness, worldManager)
{
}

void Entity::Update(const float elapsedTime)
{
    if(IsDead()) return;
    m_PhysicsCollider.ApplyForce(Vector2f{0,1000} * elapsedTime);
    m_PhysicsCollider.UpdatePhysics(elapsedTime);
}

void Entity::YouGotHit(const int damage, const Vector2f& force)
{
    m_Health -= damage;
    m_PhysicsCollider.ApplyForce(force);

    // Spawn Blood particle
}
int Entity::GetHealth() const
{
    return m_Health;
}

bool Entity::IsDead() const
{
    return m_Health <= 0;
}
const Rectf& Entity::GetRect() const
{
    return m_PhysicsCollider.GetRect();
}
Vector2f Entity::GetCenter() const
{
    return m_PhysicsCollider.GetCenter();
}
const RectPhysicsCollider& Entity::GetCollider() const
{
    return m_PhysicsCollider;
}

