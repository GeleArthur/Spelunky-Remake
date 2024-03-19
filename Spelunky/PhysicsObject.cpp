#include "pch.h"
#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(const Vector2f position):
    m_Position(position),
    m_Velocity(0, 0),
    m_PrevPosition(position)
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
