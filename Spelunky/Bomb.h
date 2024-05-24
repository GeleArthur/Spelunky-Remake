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
    static constexpr int EXPLODE_RADIUS{2}; // Is this the way to avoid const member?
    static constexpr float TIMER_START{2.4f};
    float m_Timer{TIMER_START};
    bool m_IsOnGround{};
    const SpriteSheetManager* m_SpriteSheetManager;
    const WorldManager* m_WorldManager;
};
