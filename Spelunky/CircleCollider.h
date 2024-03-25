﻿#pragma once
#include "Collider.h"

class PhysicsObject;

class CircleCollider : public Collider
{
public:
    explicit CircleCollider(const Vector2f& position, float size, PhysicsObject* owner = nullptr);
    virtual ColliderTypes GetColliderType() const override;
    virtual Vector2f GetCenterPosition() override;
    virtual void DebugDraw() override;
    Vector2f GetLocalCenterPosition() const;
    void SetLocalCenterPosition(const Vector2f& newPos);
    float GetSize() const;
    void SetSize(float newSize);
    

private:
    Vector2f m_CenterPosition;
    float m_Size;
    PhysicsObject* m_PhysicsOwner;
};
