#pragma once
#include "EntityRectCollider.h"

class Cave;
class SpriteSheetManager;

class Bomb final : public EntityRectCollider
{
public:
    explicit Bomb(WorldManager* worldManager);
    virtual EntityType GetEntityType() const override;
    virtual void Draw() const override;
    virtual void Update(float elapsedTime) override;
    void Throw(const Vector2f& position, const Vector2f& velocity);
    void Explode();

protected:
    virtual void CallBackHitTile(std::vector<std::pair<const Tile*, RayVsRectInfo>>& hitInfo) override;


private:
    const float m_TimerStart{2.4f};
    float m_Timer{m_TimerStart};
    int m_ExplodeRadius{2};
    bool m_IsOnGround{};
    const SpriteSheetManager* m_SpriteSheetManager;
    const WorldManager* m_WorldManager;
};
