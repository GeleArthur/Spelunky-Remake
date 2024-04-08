#include "pch.h"
#include "PhysicsObject.h"

#include <iostream>
#include <vector>

#include "CircleCollider.h"
#include "Collider.h"
#include "GlobalValues.h"
#include "RectCollider.h"
#include "Tile.h"
#include "utils.h"

class Tile;

PhysicsObject::PhysicsObject(Collider* collider, const std::vector<std::vector<Tile>>* tiles):
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
    switch (m_Collider->GetColliderType())
    {
    case ColliderTypes::circle:
        // TODO
        break;
    case ColliderTypes::rect:
        const RectCollider* rectCollider{reinterpret_cast<RectCollider*>(m_Collider)};
        for (int i{}; i < int(m_WorldTiles->size()); ++i)
        {
            for (int j{}; j < int(m_WorldTiles->at(i).size()); ++j)
            {
                utils::SetColor({1,1,1,1});
                const Tile* currentTile = &m_WorldTiles->at(i).at(j);
                if(currentTile->GetTileType() == TileTypes::air) continue;
                const Rectf rect = rectCollider->GetRect();
                collision_helpers::RayVsRectInfo out;
                if (!RectRayVsRect(
                    Rectf{rect.left, rect.top, rect.width, rect.height},
                    m_Velocity * elapsedTime,
                    currentTile->GetCollider()->GetRect(), out)
                    ) continue;

                utils::SetColor({1,0,0,1});
                rectCollider->DebugDraw();
                out.
                // m_Collider->SetOrigin(out.pointHit);
                m_Velocity.y = 0;
                return;
            }
        }
        break;
    }
    m_Collider->SetOrigin(m_Collider->GetOrigin() + m_Velocity * elapsedTime);
}

Collider* PhysicsObject::GetCollider() const
{
    return m_Collider;
}
