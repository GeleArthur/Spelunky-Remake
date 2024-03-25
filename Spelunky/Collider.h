﻿#pragma once
#include "CollisionHelpers.h"
struct Vector2f;

enum class ColliderTypes
{
    circle = 0b0000'0001,
    rect = 0b0000'0010
};

class Collider
{
public:
    virtual ~Collider() = default;
    virtual ColliderTypes GetColliderType() const = 0;
    virtual Vector2f GetCenterPosition() = 0;
    virtual void DebugDraw() = 0;
};
