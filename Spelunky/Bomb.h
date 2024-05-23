#pragma once
#include "EntityRectCollider.h"

class Cave;
class SpriteSheetManager;

class Bomb final : public EntityRectCollider
{
public:
    Bomb(const Vector2f& position, WorldManager* worldManager);
    virtual EntityType GetEntityType() const override;
    virtual void Draw() const override;
    virtual void Update(float elapsedTime) override;
    void Throw(const Vector2f& position, const Vector2f& velocity);
    void Explode();

private:
    const float m_TimerStart{2.4f};
    float m_Timer{m_TimerStart};
    int m_ExplodeRadius{2};
    const SpriteSheetManager* m_SpriteSheetManager;
    const WorldManager* m_WorldManager;
};
