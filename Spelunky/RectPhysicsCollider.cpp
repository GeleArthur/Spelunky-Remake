#include "pch.h"
#include "RectPhysicsCollider.h"

#include <algorithm>

#include "Cave.h"
#include "EntityManager.h"
#include "EntityRectCollider.h"
#include "Game.h"
#include "GizmosDrawer.h"
#include "utils.h"
#include "WorldManager.h"

std::vector<std::pair<const Tile*, RayVsRectInfo>> RectPhysicsCollider::m_HitsCache{};
std::vector<std::pair<const Tile*, RayVsRectInfo>> RectPhysicsCollider::m_BlocksWeHit{};
std::vector<std::pair<RayVsRectInfo, EntityRectCollider*>> RectPhysicsCollider::m_EntitiesWeHit{};

RectPhysicsCollider::RectPhysicsCollider(const Rectf& rect, const float mass, const float bounciness,
                                         WorldManager* worldManager):
    m_Rect(rect),
    m_InverseMass(1/mass),
    m_Bounciness(bounciness),
    m_WorldManager(worldManager)
{
}

void RectPhysicsCollider::DebugDraw() const
{
    GizmosDrawer::DrawRect(m_Rect);
}

const Rectf& RectPhysicsCollider::GetRect() const
{
    return m_Rect;
}

void RectPhysicsCollider::SetRect(const Rectf& rect)
{
    m_Rect = rect;
}

Vector2f RectPhysicsCollider::GetCenter() const
{
    return Vector2f{m_Rect.left + m_Rect.width / 2.0f, m_Rect.top + m_Rect.height / 2.0f};
}

void RectPhysicsCollider::SetCenter(const Vector2f& position)
{
    m_Rect = Rectf{position.x - m_Rect.width / 2.0f, position.y - m_Rect.height / 2.0f, m_Rect.width, m_Rect.height};
}

const Vector2f& RectPhysicsCollider::GetVelocity() const
{
    return m_Velocity;
}

void RectPhysicsCollider::SetVelocity(const Vector2f& newVelocity)
{
    m_Velocity = newVelocity;
}

void RectPhysicsCollider::SetVelocity(const float x, const float y)
{
    m_Velocity = Vector2f{x, y};
}
void RectPhysicsCollider::SetBounciness(const float newBounciness)
{
    m_Bounciness = newBounciness;
}
float RectPhysicsCollider::GetBounciness() const
{
    return m_Bounciness;
}

void RectPhysicsCollider::ApplyForce(const Vector2f& forceToApply)
{
    m_Velocity += forceToApply;
}

bool RectPhysicsCollider::IsOverlapping(const RectPhysicsCollider& other) const
{
    const Rectf& rect1 = m_Rect;
    const Rectf& rect2 = other.m_Rect;

    if (rect1.left + rect1.width >= rect2.left && // r1 right edge past r2 left
        rect1.left <= rect2.left + rect2.width && // r1 left edge past r2 right
        rect1.top + rect1.height >= rect2.top && // r1 top edge past r2 bottom
        rect1.top <= rect2.top + rect2.height)
    {
        return true;
    }

    return false;
}

bool RectPhysicsCollider::PredictCollision(const Vector2f& startPoint, const Vector2f& moveDirection,
                                           const RectPhysicsCollider& otherPhysicsRect, RayVsRectInfo& out) const
{
    const Rectf otherRect{otherPhysicsRect.GetRect()};
    const Rectf thisRect{GetRect()};

    const Rectf extendedRect{
        otherRect.left - thisRect.width / 2,
        otherRect.top - thisRect.height / 2,
        otherRect.width + thisRect.width,
        otherRect.height + thisRect.height
    };

    return RayCastCollision(startPoint, moveDirection, extendedRect, out);
}

bool RectPhysicsCollider::RayCastCollision(const Vector2f& startPoint, const Vector2f& moveDirection,
    const Rectf& rect, RayVsRectInfo& out)
{
    float nearTimeX = (rect.left - startPoint.x) / moveDirection.x;
    float nearTimeY = (rect.top - startPoint.y) / moveDirection.y;

    float farTimeX = ((rect.left + rect.width) - startPoint.x) / moveDirection.x;
    float farTimeY = ((rect.top + rect.height) - startPoint.y) / moveDirection.y;

    if (std::isnan(nearTimeX)) nearTimeX = 1;
    if (std::isnan(nearTimeY)) nearTimeY = 1;
    if (std::isnan(farTimeX)) farTimeX = 0;
    if (std::isnan(farTimeY)) farTimeY = 0;


    if (nearTimeX > farTimeX) std::swap(nearTimeX, farTimeX);
    if (nearTimeY > farTimeY) std::swap(nearTimeY, farTimeY);

    const float nearTime = std::max(nearTimeX, nearTimeY);
    const float farTime = std::min(farTimeX, farTimeY);
    
    if (farTime <= 0 && nearTime >= 1) // Check if line is in ray time
        return false;
    if (nearTime >= farTime || farTime <= 0 || nearTime >= 1)
    // If the outer points over shoot each other it doesn't hit
    {
        return false;
    }

    out.nearTime = nearTime;
    out.farTime = farTime;
    
    out.interSectionPoint = startPoint + moveDirection * nearTime;
    if (nearTimeX > nearTimeY) // We hit on the X side
    {
        if (moveDirection.x > 0) out.normal = Vector2f{-1, 0};
        else out.normal = Vector2f{1, 0};
    }
    else
    {
        if (moveDirection.y > 0) out.normal = Vector2f{0, -1};
        else out.normal = Vector2f{0, 1};
    }

    return true;
}

//TODO: If you build up velocity on the floor by elapsedTime we should ignore it if there is a bounch
void RectPhysicsCollider::UpdatePhysics(const float elapsedTime)
{
    const std::vector<std::vector<Tile>>& tiles = m_WorldManager->GetCave()->GetTiles();

    bool isColliding = true;

    Vector2f collidedPosition = GetCenter();
    Vector2f collidedVelocity = m_Velocity * elapsedTime;
    
    m_BlocksWeHit.clear();
    
    int limitCount = 10;
    while (isColliding && limitCount > 0)
    {
        isColliding = false;
        --limitCount;

        m_HitsCache.clear();

        // TODO: Optimise so it only checks around the collider based on the velocity
        for (int i{}; i < static_cast<int>(tiles.size()); ++i)
        {
            for (int j{}; j < static_cast<int>(tiles[i].size()); ++j)
            {
                const Tile& currentTile = tiles[i][j];
                if (currentTile.GetTileType() == TileTypes::air) continue;

                RayVsRectInfo rayResult;
                if (PredictCollision(collidedPosition, collidedVelocity, currentTile, rayResult))
                {
                    m_HitsCache.emplace_back(&currentTile, rayResult);
                }
            }
        }
        if (!m_HitsCache.empty())
        {
            std::sort(m_HitsCache.begin(), m_HitsCache.end(), [](const std::pair<const Tile*, RayVsRectInfo>& first, const std::pair<const Tile*, RayVsRectInfo>& second)
            {
                return first.second.nearTime < second.second.nearTime;
            });

            for (int i{}; i < m_HitsCache.size(); ++i)
            {
                std::pair<const Tile*, RayVsRectInfo> firstHit = m_HitsCache[i];
                m_BlocksWeHit.push_back(firstHit);
            
                if(firstHit.first->GetTileType() != TileTypes::ground && firstHit.first->GetTileType() != TileTypes::border) continue;
                
                const float t = 1 - firstHit.second.nearTime;
                const Vector2f velocityThatLeft = collidedVelocity * t;

                // float cancelBounce = m_Bounciness;
                // if(collidedVelocity.Length() <= 10*elapsedTime )
                // {
                //     cancelBounce = 0;
                // }

                const float strengthInVelocity = (-(1 + m_Bounciness) * velocityThatLeft).DotProduct(firstHit.second.normal);
                const float strengthInVelocityFull = (-(1 + m_Bounciness) * m_Velocity).DotProduct(firstHit.second.normal);
                
                m_Velocity += firstHit.second.normal * strengthInVelocityFull;
                collidedVelocity = velocityThatLeft + firstHit.second.normal * strengthInVelocity;
                collidedPosition = firstHit.second.interSectionPoint;
                isColliding = true;
                break;
            }
        }
    }
    
    Vector2f fixedVelocity;
    if(m_Velocity.SquaredLength() != 0)
    {
        m_IsLookingLeft = m_Velocity.x > 0;
        fixedVelocity = m_Velocity * elapsedTime;
    }
    else
    {
        fixedVelocity = Vector2f{m_IsLookingLeft ? 0.001f : -0.001f * elapsedTime, 0};
    }
    // Not perfect as its possible to skip an entity if hit 2 walls but the chance of that is really low.
    CheckEntityCollision(collidedPosition, fixedVelocity);
    
    collidedPosition += collidedVelocity;
    SetCenter(collidedPosition);
    
    CallBackHitTile(m_BlocksWeHit);
    CallBackHitEntity(m_EntitiesWeHit);
    
    // GizmosDrawer::SetColor({1,1,1});
    // GizmosDrawer::DrawCircle(collidedPosition, 3);
}

void RectPhysicsCollider::CheckEntityCollision(const Vector2f& position, const Vector2f& velocity) const
{
    const std::vector<EntityRectCollider*>& entities = m_WorldManager->GetEntityManager()->GetAllEntities();
    m_EntitiesWeHit.clear();
    
    for (int i{}; i < static_cast<int>(entities.size()); ++i)
    {
        if(entities[i] == this || entities[i]->IsDead())
        {
            continue;
        }

        RayVsRectInfo out;
        if(PredictCollision(position, velocity, *entities[i], out))
        {
            m_EntitiesWeHit.emplace_back(out, entities[i]);
        }
    }
}

void RectPhysicsCollider::CallBackHitTile(std::vector<std::pair<const Tile*, RayVsRectInfo>>& hitInfo)
{
}

void RectPhysicsCollider::CallBackHitEntity(std::vector<std::pair<RayVsRectInfo, EntityRectCollider*>>& hitInfo)
{
}
