#include "pch.h"
#include "PhysicsObject.h"

#include <vector>

#include "Collider.h"

class Tile;

PhysicsObject::PhysicsObject(const Vector2f position, const Collider& collider,const std::vector<std::vector<Tile>>* tiles):
    m_Position(position),
    m_Velocity(0, 0),
    m_PrevPosition(position),
    m_Collider(collider),
    m_WorldTiles(tiles)
{
}

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::UpdatePhysics(const float elapsedTime)
{
    m_Velocity += Vector2f{0, 100.f} * elapsedTime;
    m_Collider.GetCenterPosition().
    m_Position += m_Velocity * elapsedTime;
}

Collider& PhysicsObject::GetCollider()
{
    return m_Collider;
}
