#include "pch.h"
#include "PhysicsObject.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "CircleCollider.h"
#include "Collider.h"
#include "GizmosDrawer.h"
#include "GlobalValues.h"
#include "RectCollider.h"
#include "Tile.h"
#include "utils.h"

class Tile;

bool PhysicsObject::pauseAllPhysicsDebug{false};

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
    if(pauseAllPhysicsDebug) return;
    m_Velocity += Vector2f{0, 100.f} * elapsedTime;
    
    switch (m_Collider->GetColliderType())
    {
    case ColliderTypes::circle:
        // TODO
        break;
    case ColliderTypes::rect:
        const RectCollider* rectCollider{reinterpret_cast<RectCollider*>(m_Collider)};

        std::vector<collision_helpers::RayVsRectInfo> results{};

        GizmosDrawer::SetColor({0,1,0});
        GizmosDrawer::DrawLine(rectCollider->GetRect().GetCenter(), rectCollider->GetRect().GetCenter() + m_Velocity * elapsedTime);
        GizmosDrawer::DrawRect(rectCollider->GetRect() + m_Velocity * elapsedTime);

        for (int i{}; i < int(m_WorldTiles->size()); ++i)
        {
            for (int j{}; j < int(m_WorldTiles->at(i).size()); ++j)
            {
                const Tile* currentTile = &m_WorldTiles->at(i).at(j);
                if(currentTile->GetTileType() == TileTypes::air) continue;
                collision_helpers::RayVsRectInfo out;
                if (RectRayVsRect(
                    rectCollider->GetRect(),
                    m_Velocity * elapsedTime,
                    currentTile->GetCollider()->GetRect(), out)
                    )
                {
                    GizmosDrawer::SetColor({1,0,0});
                    GizmosDrawer::DrawRect(currentTile->GetCollider()->GetRect());
                    // GizmosDrawer::DrawCircle(out.pointHit, 10);

                    const float strengthInVelocity = out.normal.DotProduct(m_Velocity);
                    m_Velocity -= out.normal * strengthInVelocity;
                    results.push_back(out);
                }
            }
        }

        if(results.empty()) break;

        // std::sort(results.begin(), results.end(),
        //     [](const collision_helpers::RayVsRectInfo& l, const collision_helpers::RayVsRectInfo& r)
        // {
        //     return l.nearHit > r.nearHit;
        // });
        //
        // for (int i{}; i < int(results.size()); ++i)
        // {
        //     const float strengthInVelocity = results[i].normal.DotProduct(m_Velocity);
        //     m_Velocity -= results[i].normal * strengthInVelocity;
        // }

        // utils::SetColor({1,0,0,1});
        // rectCollider->DebugDraw();
        // m_Collider->SetOrigin(out.pointHit);

        
        break;
    }
    m_Collider->SetOrigin(m_Collider->GetOrigin() + m_Velocity * elapsedTime);
}

Collider* PhysicsObject::GetCollider() const
{
    return m_Collider;
}
