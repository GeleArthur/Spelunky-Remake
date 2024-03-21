﻿#pragma once

struct HitInfo
{
    float lambda;
    Vector2f intersectPoint;
    Vector2f normal;
};

class Collider
{
public:
    explicit Collider(const Vector2f& centerPosition);
    virtual ~Collider();
    virtual bool CheckAgainstRect(const Rectf& other, HitInfo& out);
    const Vector2f& GetCenterPosition() const;

protected:
    Vector2f m_CenterPosition;
};
