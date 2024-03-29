#include "pch.h"
#include "PhysicsObject.h"

#include <iostream>
#include <vector>

#include "CircleCollider.h"
#include "Collider.h"
#include "RectCollider.h"
#include "Tile.h"

class Tile;

PhysicsObject::PhysicsObject(const Vector2f& position, Collider* collider, const std::vector<std::vector<Tile>>* tiles):
    m_Position(position),
    m_Velocity(0, 0),
    m_Collider(collider),
    m_WorldTiles(tiles)
{
}

// PhysicsObject::PhysicsObject(const PhysicsObject& other):
//     m_Position(other.m_Position),
//     m_Velocity(other.m_Velocity),
//     m_WorldTiles(other.m_WorldTiles)
// {
//     switch (other.m_Collider->GetColliderType())
//     {
//     case ColliderTypes::circle:
//         {
//             CircleCollider* circleCollider = reinterpret_cast<CircleCollider*>(other.m_Collider);
//             m_Collider = new CircleCollider{circleCollider->GetLocalCenterPosition(), circleCollider->GetSize(), this};
//         }
//         break;
//     case ColliderTypes::rect:
//         {
//             RectCollider* rectCollider = reinterpret_cast<RectCollider*>(other.m_Collider);
//             m_Collider = new RectCollider{rectCollider->GetRect(), this};
//         }
//         break;
//     }
// }

PhysicsObject::~PhysicsObject()
{
    delete m_Collider;
}

void PhysicsObject::UpdatePhysics(const float elapsedTime)
{
    m_Velocity += Vector2f{0, 100.f} * elapsedTime;
    m_Position += m_Velocity * elapsedTime;
    
    for (int i{}; i < m_WorldTiles->size(); ++i)
    {
        for (int j{}; j < m_WorldTiles->at(i).size(); ++j)
        {
            collision_helpers::HitInfo out;
            if(collision_helpers::CheckAgainstWorld(m_Collider, m_WorldTiles, out))
            {
                // WE HIT!!!!
                std::cout << "WE HIT";
            }
            
            
            // CollisionHelpers::RectVsRect()
            // m_WorldTiles->at(i).at(j).GetWorldPosition()
        }
    }
    

}

Vector2f PhysicsObject::GetPosition() const
{
    return m_Position;
}

void PhysicsObject::Teleport(const Vector2f& newPosition)
{
    m_Position = newPosition;
}

// PhysicsObject& PhysicsObject::operator=(const PhysicsObject& rhs)
// {
//     if(&rhs != this)
//     {
//         this->m_Bounciness = rhs.m_Bounciness;
//         delete this->m_Collider;
//         this->m_Collider = new Collider(rhs.m_Collider);
//     }
//     return *this;
// }

Collider* PhysicsObject::GetCollider() const
{
    return m_Collider;
}
