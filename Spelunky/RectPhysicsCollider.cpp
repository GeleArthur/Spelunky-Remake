#include "pch.h"
#include "RectPhysicsCollider.h"

#include <algorithm>

#include "Cave.h"
#include "CirclePhysicsCollider.h"
#include "GizmosDrawer.h"
#include "utils.h"
#include "WorldManager.h"

RectPhysicsCollider::RectPhysicsCollider(const Rectf& rect, const float mass, const float bounciness, WorldManager* worldManager):
    m_Rect(rect),
    m_Mass(mass),
    m_Bounciness(bounciness),
    m_WorldManager(worldManager)
{
}

ColliderTypes RectPhysicsCollider::GetColliderType() const
{
    return ColliderTypes::rect;
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

bool RectPhysicsCollider::IsOverlapping(const CirclePhysicsCollider& other) const
{
    // TODO
    return false;
}

bool RectPhysicsCollider::IsOverlapping(const Collider& other) const
{
    switch (other.GetColliderType())
    {
    case ColliderTypes::circle:
        return IsOverlapping(reinterpret_cast<const CirclePhysicsCollider&>(other));
    case ColliderTypes::rect:
        return IsOverlapping(reinterpret_cast<const RectPhysicsCollider&>(other));
    }
    throw;
}

bool RectPhysicsCollider::PredictCollision(const Vector2f& startPoint, const Vector2f& moveDirection, const RectPhysicsCollider& otherPhysicsRect, RayVsRectInfo& out)
{
    if(moveDirection.x == 0 && moveDirection.y == 0)
        return false;
    
    Rectf otherRect{otherPhysicsRect.GetRect()};
    Rectf thisRect{GetRect()};

    const Rectf extendedRect{
        otherRect.left - thisRect.width / 2,
        otherRect.top - thisRect.height / 2,
        otherRect.width + thisRect.width,
        otherRect.height + thisRect.height
    };

    GizmosDrawer::SetColor({0,1,0});
    GizmosDrawer::DrawRect(extendedRect);
    
    Vector2f rayOrigin = startPoint;
    Vector2f rayDirection = moveDirection;
    // GizmosDrawer::SetColor({1,0,0});
    // GizmosDrawer::DrawLine(rayOrigin, rayOrigin + rayDirection);
    
    float nearTimeX = (extendedRect.left - rayOrigin.x) / rayDirection.x;
    float nearTimeY = (extendedRect.top - rayOrigin.y) / rayDirection.y;

    float farTimeX = ((extendedRect.left + extendedRect.width) - rayOrigin.x) / rayDirection.x;
    float farTimeY = ((extendedRect.top + extendedRect.height) - rayOrigin.y) / rayDirection.y;

    if (std::isnan(nearTimeX))nearTimeX = 0;
    if (std::isnan(nearTimeY)) nearTimeY = 0;
    if (std::isnan(farTimeX)) farTimeX = 0;
    if (std::isnan(farTimeY)) farTimeY = 0;
    

    
    if (nearTimeX > farTimeX) std::swap(nearTimeX, farTimeX);
    if (nearTimeY > farTimeY) std::swap(nearTimeY, farTimeY);
    
    /*
    GizmosDrawer::SetColor({1,0,0});
    GizmosDrawer::DrawCircle(rayOrigin + rayDirection * nearTimeX, 4);
    GizmosDrawer::DrawQText(rayOrigin + rayDirection * nearTimeX, "N X: " + std::to_string(nearTimeX));
    GizmosDrawer::DrawCircle(rayOrigin + rayDirection * nearTimeY, 4);
    GizmosDrawer::DrawQText(rayOrigin + rayDirection * nearTimeY, "N Y: " + std::to_string(nearTimeY));
    
    GizmosDrawer::SetColor({0,1,0});
    GizmosDrawer::DrawCircle(rayOrigin + rayDirection * farTimeX, 4);
    GizmosDrawer::DrawQText(rayOrigin + rayDirection * farTimeX, "F X" + std::to_string(farTimeX));
    GizmosDrawer::DrawCircle(rayOrigin + rayDirection * farTimeY, 4);
    GizmosDrawer::DrawQText(rayOrigin + rayDirection * farTimeY, "F Y" + std::to_string(farTimeY));
    */

    
    float nearTime = std::max(nearTimeX, nearTimeY);
    float farTime = std::min(farTimeX, farTimeY);

    // GizmosDrawer::SetColor({1,0,0});
    // GizmosDrawer::DrawCircle(rayOrigin + rayDirection * nearTime, 4);
    // GizmosDrawer::DrawQText(rayOrigin + rayDirection * nearTime, "Near " + std::to_string(nearTime));
    //
    // GizmosDrawer::SetColor({0,1,0});
    // GizmosDrawer::DrawCircle(rayOrigin + rayDirection * farTime, 4);
    // GizmosDrawer::DrawQText(rayOrigin + rayDirection * farTime, "Far " + std::to_string(farTime));
    
    if(farTime <= 0 && nearTime >= 1) // Check if line is in ray time
        return false;
    if(nearTime >= farTime || farTime <= 0 || nearTime >= 1) // If the outer points over shoot each other it doesn't hit
    {
        return false;
    }
    
    out.nearTime = nearTime;
    out.farTime = farTime;
    
    // GizmosDrawer::SetColor({1,0,0});
    // GizmosDrawer::DrawRect(extendedRect);

    out.interSectionPoint = rayOrigin + rayDirection * nearTime;
    if(nearTimeX > nearTimeY) // We hit on the X side
    {
        if(rayDirection.x > 0) out.normal = Vector2f{-1, 0};
        else out.normal = Vector2f{1, 0};
    }
    else
    {
        if(rayDirection.y > 0) out.normal = Vector2f{0, -1};
        else out.normal = Vector2f{0, 1};
    }

    // GizmosDrawer::DrawCircle(out.interSectionPoint, 5);
    // GizmosDrawer::DrawLine(out.interSectionPoint, out.interSectionPoint + out.normal * 10);

    
    
    // if (nearTimeX >= farTimeY || nearTimeY >= farTimeX) return false;
    //
    // out.farHit = std::min(farTimeX, farTimeY);
    // out.farHit = std::min(farTimeX, farTimeY);
    //
    // if (out.farHit < 0)
    //     return false;
    // if (out.nearHit > 1.0)
    //     return false;
    //
    // out.pointHit = rayOrigin + (rayDir * out.nearHit);
    //
    // if (nearTimeX > nearTimeY)
    // {
    //     if (rayDir.x < 0) out.normal = Vector2f{1, 0};
    //     else out.normal = Vector2f{-1, 0};
    // }
    // else
    // {
    //     if (rayDir.y < 0) out.normal = Vector2f{0, 1};
    //     else out.normal = Vector2f{0, -1};
    // }

    return true;
}

bool RectPhysicsCollider::PredictCollision(const CirclePhysicsCollider& other)
{
    return false;
}


void RectPhysicsCollider::UpdatePhysics(float elapsedTime)
{
    const std::vector<std::vector<Tile>>* tiles = m_WorldManager->GetCave()->GetTiles();

    bool isColliding = true;

    Vector2f collidedPosition = GetCenter();
    Vector2f collidedVelocity = m_Velocity;
    
    GizmosDrawer::SetColor({1,1,1});
    GizmosDrawer::DrawLine(GetCenter(), GetCenter() + m_Velocity);

    int limitCount = 10;

    Vector2f prevIntersection = collidedPosition;

    // RayVsRectInfo rayResult;
    // if(PredictCollision(collidedPosition, collidedVelocity, tiles->at(0).at(0), rayResult))
    // {
    //     GizmosDrawer::SetColor({1,0,0});
    //     GizmosDrawer::DrawCircle(rayResult.interSectionPoint, 5);
    // }
    
    while (isColliding && limitCount > 0)
    {
        isColliding = false;
        --limitCount;

        std::vector<std::pair<const Tile*, RayVsRectInfo>> hits;
        
        for (int i{}; i < int(tiles->size()); ++i)
        {
            for (int j{}; j < int(tiles->at(i).size()); ++j)
            {
                const Tile& currentTile = tiles->at(i).at(j);
                if (currentTile.GetTileType() != TileTypes::ground) continue;

                RayVsRectInfo rayResult;
                if(PredictCollision(collidedPosition, collidedVelocity, currentTile, rayResult))
                {
                    hits.push_back(std::pair(&currentTile,rayResult));
                }
            }
        }
        if (!hits.empty())
        {
            std::sort(hits.begin(), hits.end(), [](const std::pair<const Tile*, RayVsRectInfo>& first, const std::pair<const Tile*, RayVsRectInfo>& second)
            {
                return first.second.nearTime < second.second.nearTime;
            });

            std::pair<const Tile*, RayVsRectInfo> firstHit = hits.at(0);
            
            float t = 1 - firstHit.second.nearTime;
            const Vector2f velocityThatLeft = collidedVelocity * t;
            
            float bounce = m_Bounciness;
            float strengthInVelocity = (-(1+bounce) * velocityThatLeft).DotProduct(firstHit.second.normal);
            
            GizmosDrawer::DrawLine(collidedPosition + collidedVelocity, collidedPosition + collidedVelocity + firstHit.second.normal * strengthInVelocity);
            
            collidedVelocity += firstHit.second.normal * strengthInVelocity;
            collidedPosition += collidedVelocity /*+ firstHit.second.normal * strengthInVelocity*/;
            
            // m_balls[j].velocity = m_balls[j].velocity - (1 / m_balls[j].mass) * scaledVelocityStrength *collisionNormal;

            // Old perfect bounce velocity
            
            // float t = 1 - firstHit.second.nearTime;
            // Vector2f velocityThatLeft = collidedVelocity * t;
            //
            // Vector2f reflectedVelocity = velocityThatLeft.Reflect(firstHit.second.normal);

            // collidedPosition = firstHit.interSectionPoint;
            // collidedVelocity = reflectedVelocity;
            // isColliding = true;

            GizmosDrawer::SetColor({1,0,0});
            GizmosDrawer::DrawCircle(firstHit.second.interSectionPoint, 5);
            GizmosDrawer::DrawLine(prevIntersection, firstHit.second.interSectionPoint);

            prevIntersection = firstHit.second.interSectionPoint;
            

            // for (int i{}; i < int(hits.size()); ++i)
            // {
            //     GizmosDrawer::SetColor({0,std::abs((float(i)/float(hits.size())-1.0f)),0});
            //     GizmosDrawer::DrawCircle(hits.at(i).interSectionPoint, 5);
            //     // GizmosDrawer::DrawLine(hits.at(i).interSectionPoint, hits.at(i).interSectionPoint + hits.at(i).normal * 10);
            // }
        }
        else
        {
            // GizmosDrawer::DrawCircle(collidedPosition + collidedVelocity, 10);
            // GizmosDrawer::DrawQText(collidedPosition + collidedVelocity, std::to_string(limitCount));
            // GizmosDrawer::DrawLine(prevIntersection, collidedPosition + collidedVelocity);
        }

        
    }
}

void RectPhysicsCollider::CallBackHitTile(Tile* tileHit)
{
}

void RectPhysicsCollider::CallBackHitEntity(Entity* entityHit)
{
}
