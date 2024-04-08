#include "pch.h"
#include "CollisionHelpers.h"

#include <iostream>
#include <vector>

#include "CircleCollider.h"
#include "Collider.h"
#include "RectCollider.h"
#include "Tile.h"
#include "utils.h"

bool collision_helpers::CircleVsCircle(const CircleCollider& circle1, const CircleCollider& circle2, HitInfo& out)
{
    const Vector2f distance = (circle2.GetCenterPosition() - circle1.GetCenterPosition());
    if(distance.SquaredLength() > circle1.GetSize()*circle1.GetSize()+circle2.GetSize()*circle2.GetSize())
    {
        out.normal = distance.Normalized();
        // out.lambda = ??????
        out.intersectPoint = circle1.GetCenterPosition() + distance/2; // Correct???
        
        return true;
    }
    
    return false;
}

bool collision_helpers::RectVsRect(const RectCollider& rect1, const RectCollider& rect2, HitInfo& out)
{
    Rectf rectData1 = rect1.GetRect();
    Rectf rectData2 = rect2.GetRect();

    Vector2f centerRect1 = Vector2f{rectData1.left + rectData1.width/2, rectData1.top + rectData1.height/2};
    
    if(rectData1.left + rectData1.width >= rectData2.left &&    // r1 right edge past r2 left
      rectData1.left <= rectData2.left + rectData2.width &&    // r1 left edge past r2 right
      rectData1.top + rectData1.height >= rectData2.top &&    // r1 top edge past r2 bottom
      rectData1.top <= rectData2.top + rectData2.height)
    {
        // out.intersectPoint =
        
        
        return true;
    }
    
    return false;
}

bool collision_helpers::CircleVsRect(const CircleCollider& circle, const RectCollider& rect1, HitInfo& out)
{
    const Vector2f centerPosCircle = circle.GetCenterPosition();
    Vector2f intersectPoint{circle.GetCenterPosition()};
    const Rectf rectOther{rect1.GetRect()};
    
    if(centerPosCircle.x < rectOther.left) intersectPoint.x = rectOther.left;
    else if (centerPosCircle.x > rectOther.left + rectOther.width) intersectPoint.x = rectOther.left + rectOther.width;

    if(centerPosCircle.y < rectOther.top) intersectPoint.y = rectOther.top;
    else if (centerPosCircle.y > rectOther.top + rectOther.height) intersectPoint.y = rectOther.top + rectOther.height;
    
    const Vector2f distance = intersectPoint - centerPosCircle;
    const float overlap = circle.GetSize() - distance.Length();
    
    if(overlap > 0)
    {
        if(distance.SquaredLength() <= 0)
        {
            std::cout << "Physics are going to fast!!!" << '\n';
        }
        out.intersectPoint = intersectPoint;
        out.normal = -distance.Normalized();
        out.lambda = overlap;
        return true;
    }
    return false;
}

bool collision_helpers::RayVsRect(const Rectf& rect, const Vector2f& rayOrigin, const Vector2f& rayDir, RayVsRectInfo& out )
{
    float nearTimeX = (rect.left - rayOrigin.x) / rayDir.x;
    float nearTimeY = (rect.top - rayOrigin.y) / rayDir.y;
    
    float farTimeX = ((rect.left + rect.width) - rayOrigin.x) / rayDir.x;
    float farTimeY = ((rect.top + rect.height) - rayOrigin.y) / rayDir.y;
    
    if(nearTimeX > farTimeX) std::swap(nearTimeX, farTimeX);
    if(nearTimeY > farTimeY) std::swap(nearTimeY, farTimeY);
    
    if(nearTimeX >= farTimeY || nearTimeY >= farTimeX) return false;
    
    out.nearHit = std::max(nearTimeX, nearTimeY);
    out.farHit = std::min(farTimeX, farTimeY);

    if (out.farHit < 0)
        return false;
        
    out.pointHit = rayOrigin + rayDir * out.nearHit;

    if(nearTimeX > nearTimeY)
    {
        if(rayDir.x < 0) out.normal = Vector2f{1,0};
        else out.normal = Vector2f{-1,0};
    }
    else
    {
        if(rayDir.y < 0) out.normal = Vector2f{0,1};
        else out.normal = Vector2f{0,-1};
    }
        
    return true;
}

bool collision_helpers::RectRayVsRect(const Rectf& movingRect, const Vector2f& rayDirection, const Rectf& staticRect, RayVsRectInfo& out)
{
    const Rectf extendedRect{
        staticRect.left - movingRect.width/2,
        staticRect.top - movingRect.height/2,
        staticRect.width + movingRect.width,
        staticRect.height + movingRect.height
    };
    
    if(RayVsRect(extendedRect, Vector2f{movingRect.left + movingRect.width/2, movingRect.top + movingRect.height/2}, rayDirection, out))
    {
        return out.nearHit < 1.0;
    }
    
    return false;
}

bool collision_helpers::CircleRayVsRect(
    const CircleCollider& movingCircle,
    const Vector2f& rayDirection,
    const Rectf& staticRect,
    RayVsRectInfo& out)
{
    return false;
}
