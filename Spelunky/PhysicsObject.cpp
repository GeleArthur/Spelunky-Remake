#include "pch.h"
#include "PhysicsObject.h"

#include <vector>

class Tile;

PhysicsObject::PhysicsObject(const Vector2f position, const std::vector<std::vector<Tile>>& tiles):
    m_Position(position),
    m_Velocity(0, 0),
    m_PrevPosition(position),
    m_WorldTiles(tiles)
{
}

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::UpdatePhysics(const float elapsedTime)
{
    
    
    m_Velocity += Vector2f{0, 100.f} * elapsedTime;
    m_Position += m_Velocity * elapsedTime;
}
