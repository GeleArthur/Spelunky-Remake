#include "pch.h"
#include "CollisionHelpers.h"

#include <vector>

#include "CircleCollider.h"
#include "Collider.h"
#include "RectCollider.h"
#include "Tile.h"
#include "utils.h"

bool CollisionHelpers::CheckCollision(const Collider& collider1, const Collider& collider2, HitInfo& out)
{
    const char collider1Type = static_cast<char>(collider1.GetColliderType());
    const char collider2Type = static_cast<char>(collider2.GetColliderType());

    // Real 
    switch (collider1Type | collider2Type)
    {
    case 0b0000'0001:
        return  CircleVsCircle(reinterpret_cast<const CircleCollider&>(collider1),
                       reinterpret_cast<const CircleCollider&>(collider2), out);
    case 0b0000'0010:
        return RectVsRect(reinterpret_cast<const RectCollider&>(collider1),
                   reinterpret_cast<const RectCollider&>(collider2), out);
    case 0b0000'0011:
        if(collider1Type == 0b0000'0001)
        {
            return RectVsCircle(reinterpret_cast<const RectCollider&>(collider2), reinterpret_cast<const CircleCollider&>(collider1),  out);
        }
        else
        {
            return RectVsCircle(reinterpret_cast<const RectCollider&>(collider1), reinterpret_cast<const CircleCollider&>(collider2),  out);
        }
    default:
        throw;
        return false;
    }
}

bool CollisionHelpers::CircleVsCircle(const CircleCollider& circle1, const CircleCollider& circle2, HitInfo& out)
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

bool CollisionHelpers::RectVsRect(const RectCollider& rect1, const RectCollider& rect2, HitInfo& out)
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

bool CollisionHelpers::RectVsCircle(const RectCollider& rect1, const CircleCollider& circle, HitInfo& out)
{
    utils::DrawEllipse(Vector2f{rect1.GetRect().left, rect1.GetRect().top}, circle.GetSize(), circle.GetSize());
    utils::DrawEllipse(Vector2f{rect1.GetRect().left + rect1.GetRect().width, rect1.GetRect().top}, circle.GetSize(), circle.GetSize());
    utils::DrawEllipse(Vector2f{rect1.GetRect().left, rect1.GetRect().top + rect1.GetRect().height }, circle.GetSize(), circle.GetSize());
    utils::DrawEllipse(Vector2f{rect1.GetRect().left + rect1.GetRect().width, rect1.GetRect().top + rect1.GetRect().height}, circle.GetSize(), circle.GetSize());

    
    const Vector2f centerPosCircle = circle.GetCenterPosition();
    Vector2f sidesToTest{circle.GetCenterPosition()};
    const Rectf other{rect1.GetRect()};
    
    if(centerPosCircle.x < other.left) sidesToTest.x = other.left;
    else if (centerPosCircle.x > other.left + other.width) sidesToTest.x = other.left + other.width;

    if(centerPosCircle.y < other.top) sidesToTest.y = other.top;
    else if (centerPosCircle.y > other.top + other.height) sidesToTest.y = other.top + other.height;
    
    utils::DrawEllipse(sidesToTest, circle.GetSize(), circle.GetSize());

    const Vector2f distance = centerPosCircle - sidesToTest;
    
    if(distance.SquaredLength() <= circle.GetSize()*circle.GetSize())
    {
        out.intersectPoint = sidesToTest;
        out.normal = distance.Normalized();
        out.lambda = 0; // ????? 
        return true;
    }
    return false;
}

bool CollisionHelpers::CheckAgainstWorld(const Collider* collider, const std::vector<std::vector<Tile>>* worldTiles, HitInfo& out)
{
    switch(collider->GetColliderType())
    {
    case ColliderTypes::circle:
        
        return false;
    case ColliderTypes::rect:
        
        return false;
    }

    return false;
    
}
