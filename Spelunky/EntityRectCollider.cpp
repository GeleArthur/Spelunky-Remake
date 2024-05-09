#include "pch.h"
#include "EntityRectCollider.h"

EntityRectCollider::EntityRectCollider(const Rectf& collider, const float mass, const float bounciness, WorldManager* worldManager):
    Entity(),
    RectPhysicsCollider(collider, mass, bounciness, worldManager)
{
}

ColliderTypes EntityRectCollider::GetColliderType() const
{
    return RectPhysicsCollider::GetColliderType();
}

void EntityRectCollider::Update(const float elapsedTime)
{
    ApplyForce(Vector2f{0,1000} * elapsedTime);
    UpdatePhysics(elapsedTime);
}
