#pragma once
#include <functional>
#include <vector>

class WorldManager;
class Entity;
class Tile;

struct RayVsRectInfo
{
    Vector2f interSectionPoint;
    Vector2f normal;
    float nearTime;
    float farTime;
};

class RectPhysicsCollider final
{
public:
    explicit RectPhysicsCollider(const Rectf& rect, float mass, float bounciness, WorldManager* worldManager);
    
    // virtual ColliderTypes GetColliderType() const override;
    
    void DebugDraw() const;
    const Rectf& GetRect() const;
    void SetRect(const Rectf& rect);

    Vector2f GetCenter() const;
    void SetCenter(const Vector2f& position);

    const Vector2f& GetVelocity() const;
    void SetVelocity(const Vector2f& newVelocity);
    void SetVelocity(float x, float y);
    void SetBounciness(float newBounciness);
    float GetBounciness() const;
    void ApplyForce(const Vector2f& forceToApply);

    // Collision checks
    bool IsOverlapping(const RectPhysicsCollider& other) const;
    bool PredictCollision(const Vector2f& startPoint, const Vector2f& moveDirection, const RectPhysicsCollider& otherPhysicsRect, RayVsRectInfo& out) const;
    void UpdatePhysics(float elapsedTime);
    
    void CheckEntityCollision(const Vector2f& position, const Vector2f& velocity);
    static bool RayCastCollision(const Vector2f& startPoint, const Vector2f& moveDirection, const Rectf& rect, RayVsRectInfo& out);

    const std::vector<std::pair<const Tile*, RayVsRectInfo>>& GetTilesWeHit();
    const std::vector<std::pair<RayVsRectInfo, Entity*>>& GetEntitiesWeHit();

private:
    Rectf m_Rect;
    Vector2f m_Velocity{};

    float m_InverseMass;
    float m_Bounciness;
    bool m_IsLookingLeft{};

    WorldManager* m_WorldManager;

    std::vector<std::pair<const Tile*, RayVsRectInfo>> m_BlocksWeHit;
    std::vector<std::pair<RayVsRectInfo, Entity*>> m_EntitiesWeHit;

    // cache vector memory so the array can be reused
    static std::vector<std::pair<const Tile*, RayVsRectInfo>> m_HitsCache;
};
