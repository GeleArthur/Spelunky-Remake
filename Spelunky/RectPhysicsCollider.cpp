#include "pch.h"
#include "RectPhysicsCollider.h"

#include "CirclePhysicsCollider.h"
#include "GizmosDrawer.h"
#include "utils.h"

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
    return m_Rect.GetCenter();
}

const Vector2f& RectPhysicsCollider::GetVelocity() const
{
    return m_Velocity;
}

void RectPhysicsCollider::SetVelocity(const Vector2f& newVelocity)
{
    m_Velocity = newVelocity;
}

void RectPhysicsCollider::ApplyForce(const Vector2f& forceToApply)
{
    m_Velocity += forceToApply;
}

bool RectPhysicsCollider::IsOverlapping(const RectPhysicsCollider& other)
{
    
}

bool RectPhysicsCollider::IsOverlapping(const CirclePhysicsCollider& other)
{
}

bool RectPhysicsCollider::IsOverlapping(const Collider& other)
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
    
}

bool RectPhysicsCollider::PredictCollision(const CirclePhysicsCollider& other)
{
    
}
