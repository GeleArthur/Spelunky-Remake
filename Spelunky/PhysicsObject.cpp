#include "pch.h"
#include "PhysicsObject.h"
#include <vector>
#include "Collider.h"

class Tile;

PhysicsObject::PhysicsObject(const Vector2f& position, Collider* collider, const std::vector<std::vector<Tile>>* tiles):
    m_Position(position),
    m_Velocity(0, 0),
    m_Collider(collider),
    m_WorldTiles(tiles)
{
}

PhysicsObject::~PhysicsObject()
{
    delete m_Collider;
}

void PhysicsObject::UpdatePhysics(const float elapsedTime)
{
    m_Velocity += Vector2f{0, 100.f} * elapsedTime;
    m_Collider->GetCenterPosition();
}

Vector2f PhysicsObject::GetPosition() const
{
    return m_Position;
}

void PhysicsObject::Teleport(const Vector2f& newPosition)
{
    m_Position = newPosition;
}

Collider* PhysicsObject::GetCollider() const
{
    return m_Collider;
}
