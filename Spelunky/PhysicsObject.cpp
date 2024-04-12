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
        std::vector<const Tile*> tilePointer_DEBUG{};

        GizmosDrawer::SetColor({0,1,0});
        GizmosDrawer::DrawLine(rectCollider->GetRect().GetCenter(), rectCollider->GetRect().GetCenter() + m_Velocity * elapsedTime);
        GizmosDrawer::DrawRect(rectCollider->GetRect() + m_Velocity * elapsedTime);

        for (int i{}; i < int(m_WorldTiles->size()); ++i)
        {
            for (int j{}; j < int(m_WorldTiles->at(i).size()); ++j)
            {
                const Tile* currentTile = &m_WorldTiles->at(i).at(j);
                if(currentTile->GetTileType() == TileTypes::air || currentTile->GetTileType() == TileTypes::entrance || currentTile->GetTileType() == TileTypes::exit) continue;
                collision_helpers::RayVsRectInfo out;
                if (RectRayVsRect(
                    rectCollider->GetRect(),
                    m_Velocity * elapsedTime,
                    currentTile->GetCollider()->GetRect(), out)
                    )
                {
                    // GizmosDrawer::SetColor({1,0,0});
                    // GizmosDrawer::DrawRect(currentTile->GetCollider()->GetRect());
                    // GizmosDrawer::DrawCircle(out.pointHit, 10);
                    
                    // const float strengthInVelocity = out.normal.DotProduct(m_Velocity);
                    // m_Velocity -= out.normal * strengthInVelocity;
                    tilePointer_DEBUG.push_back(currentTile);
                    results.push_back(out);
                }
            }
        }

        if(results.empty()) break;

        // std::sort(results.begin(), results.end(),
        //     [](const collision_helpers::RayVsRectInfo& l, const collision_helpers::RayVsRectInfo& r)
        // {
        //     return l.farHit < r.farHit;
        // });

        bool isSorting = true;
        while (isSorting)
        {
            isSorting = false;
            for (int i{}; i < results.size()-1; ++i)
            {
                if(results[i].nearHit > results[i+1].nearHit)
                {
                    std::swap(results[i], results[i+1]);
                    std::swap(tilePointer_DEBUG[i], tilePointer_DEBUG[i+1]);
                    isSorting = true;
                }
            }
        }
        
        for (int i{}; i < int(results.size()); ++i)
        {
            if(i == 0 ) GizmosDrawer::SetColor({0,0,1});
            if(i == 1 ) GizmosDrawer::SetColor({0,1,1});
            if(i == 2 ) GizmosDrawer::SetColor({1,0,1});
            GizmosDrawer::DrawRect(tilePointer_DEBUG[i]->GetCollider()->GetRect());
            
            std::cout << i << ": " << results[i].nearHit << " ";
            collision_helpers::RayVsRectInfo out;
            if (RectRayVsRect(
                rectCollider->GetRect(),
                m_Velocity * elapsedTime,
                tilePointer_DEBUG[i]->GetCollider()->GetRect(), out)
                )
            {
                // GizmosDrawer::DrawCircle(out.pointHit, 10);
                const float strengthInVelocity = out.normal.DotProduct(m_Velocity);
                m_Velocity -= out.normal * strengthInVelocity;
            }
        }
        std::cout << '\n';

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
