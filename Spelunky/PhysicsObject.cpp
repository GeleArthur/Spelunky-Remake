#include "pch.h"
#include "PhysicsObject.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "CirclePhysicsCollider.h"
#include "Collider.h"
#include "GizmosDrawer.h"
#include "GlobalValues.h"
#include "RectPhysicsCollider.h"
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

PhysicsObject::PhysicsObject(const PhysicsObject& other)
{
    switch (other.m_Collider->GetColliderType())
    {
    case ColliderTypes::circle:
        m_Collider = new CirclePhysicsCollider{*reinterpret_cast<CirclePhysicsCollider*>(other.GetCollider())};
        break;
    case ColliderTypes::rect:
        m_Collider = new RectPhysicsCollider{*reinterpret_cast<RectPhysicsCollider*>(other.GetCollider())};
        break;
    }
    m_WorldTiles = other.m_WorldTiles;
}

PhysicsObject& PhysicsObject::operator=(const PhysicsObject& other)
{
    if(this != &other)
    {
        switch (other.m_Collider->GetColliderType())
        {
        case ColliderTypes::circle:
            m_Collider = new CirclePhysicsCollider{*reinterpret_cast<CirclePhysicsCollider*>(other.GetCollider())};
            break;
        case ColliderTypes::rect:
            m_Collider = new RectPhysicsCollider{*reinterpret_cast<RectPhysicsCollider*>(other.GetCollider())};
            break;
        }
    }
    
    return *this;
}

void PhysicsObject::UpdatePhysics(const float elapsedTime)
{
    if(pauseAllPhysicsDebug) return;
    m_Velocity += Vector2f{0, 1000.f} * elapsedTime;
    
    switch (m_Collider->GetColliderType())
    {
    case ColliderTypes::circle:
        // TODO
        break;
    case ColliderTypes::rect:
        const RectPhysicsCollider* rectCollider{reinterpret_cast<RectPhysicsCollider*>(m_Collider)};

        std::vector<collision_helpers::RayVsRectInfo> results{};
        std::vector<const Tile*> tilePointer_DEBUG{};
        
        // GizmosDrawer::SetColor({0,1,0});
        // GizmosDrawer::DrawLine(rectCollider->GetRect().GetCenter(), rectCollider->GetRect().GetCenter() + m_Velocity * elapsedTime);
        // GizmosDrawer::DrawRect(rectCollider->GetRect() + m_Velocity * elapsedTime);
        
        m_IsOnGround = false;
        
        for (int i{}; i < int(m_WorldTiles->size()); ++i)
        {
            for (int j{}; j < int(m_WorldTiles->at(i).size()); ++j)
            {
                const Tile* currentTile = &m_WorldTiles->at(i).at(j);
                if(currentTile->GetTileType() != TileTypes::ground) continue;
                collision_helpers::RayVsRectInfo out;
                if (RectRayVsRect(
                    rectCollider->GetRect(),
                    m_Velocity * elapsedTime,
                    currentTile->GetCollider()->GetRect(), out)
                    )
                {
                    tilePointer_DEBUG.push_back(currentTile);
                    results.push_back(out);
                }
            }
        }
        
        if(results.empty()) break;

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
            // GizmosDrawer::DrawRect(tilePointer_DEBUG[i]->GetCollider()->GetRect());
            
            collision_helpers::RayVsRectInfo out;
            if (RectRayVsRect(
                rectCollider->GetRect(),
                m_Velocity * elapsedTime,
                tilePointer_DEBUG[i]->GetCollider()->GetRect(), out)
                )
            {
                if(out.normal.y < 0)
                    m_IsOnGround = true;
                
                const float strengthInVelocity = out.normal.DotProduct(m_Velocity);
                m_Velocity -= out.normal * strengthInVelocity;
                // GetCollider()->SetOrigin(out.pointHit);
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
