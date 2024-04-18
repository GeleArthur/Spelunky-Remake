#include "pch.h"
#include "RectPhysicsCollider.h"

#include "CirclePhysicsCollider.h"
#include "GizmosDrawer.h"
#include "utils.h"
#include "WorldManager.h"

RectPhysicsCollider::RectPhysicsCollider(const Rectf& rect):
    m_Rect(rect)
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
    return Vector2f{m_Rect.left + m_Rect.width/2.0f, m_Rect.top + m_Rect.height/2.0f};
}

void RectPhysicsCollider::SetCenter(const Vector2f& position)
{
    m_Rect = Rectf{position.x - m_Rect.width/2.0f, position.y - m_Rect.height/2.0f, m_Rect.width, m_Rect.height};
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
    const Rectf rect1 = m_Rect;
    const Rectf rect2 = other.GetRect();
    
    if(rect1.left + rect1.width >= rect2.left &&    // r1 right edge past r2 left
      rect1.left <= rect2.left + rect2.width &&    // r1 left edge past r2 right
      rect1.top + rect1.height >= rect2.top &&    // r1 top edge past r2 bottom
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

bool RectPhysicsCollider::PredictCollision(const RectPhysicsCollider& other)
{
    
    
    return false;
}

bool RectPhysicsCollider::PredictCollision(const CirclePhysicsCollider& other)
{
    
    
    return false;
}

void RectPhysicsCollider::UpdatePhysics()
{
}

