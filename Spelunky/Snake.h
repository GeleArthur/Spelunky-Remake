﻿#pragma once
#include "Enemy.h"
#include "EntityRectCollider.h"

class Cave;
class SpriteSheetManager;

class Snake: public EntityRectCollider
{
public:
    Snake(const Vector2f& position, WorldManager* worldManager);

    virtual void Draw() const override;
    virtual void Update(float elapsedTime) override;
    virtual EntityType GetEntityType() const override;

private:

    bool m_MovingLeft{};
    SpriteSheetManager* m_SpriteSheetManager;
    Cave* m_Cave;
};
