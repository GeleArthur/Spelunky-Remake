#pragma once
#include <functional>

#include "Collider.h"

class WorldManager;
class Entity;
class Tile;
class CirclePhysicsCollider;

struct RayVsRectInfo
{
    Vector2f interSectionPoint;
    Vector2f normal;
    float nearTime;
    float farTime;
};

class RectPhysicsCollider : public Collider
{
public:
    explicit RectPhysicsCollider(const Rectf& rect, float mass, float bounciness, WorldManager* worldManager);
    virtual ~RectPhysicsCollider() override = default;
    RectPhysicsCollider(const RectPhysicsCollider& other) = default;
    RectPhysicsCollider& operator=(const RectPhysicsCollider& other) = default;
    RectPhysicsCollider(RectPhysicsCollider && other) = default;
    RectPhysicsCollider& operator=(RectPhysicsCollider&& other) = default;
    
    virtual ColliderTypes GetColliderType() const override;
    
    void DebugDraw() const;
    const Rectf& GetRect() const;
    void SetRect(const Rectf& rect);
    
    Vector2f GetCenter() const;
    void SetCenter(const Vector2f& position);

    const Vector2f& GetVelocity() const;
    void SetVelocity(const Vector2f& newVelocity);
    void SetVelocity(float x, float y);
    void ApplyForce(const Vector2f& forceToApply);

    // Collision checks
    bool IsOverlapping(const RectPhysicsCollider& other) const;
    bool IsOverlapping(const CirclePhysicsCollider& other) const;
    bool IsOverlapping(const Collider& other) const;

    bool PredictCollision(const Vector2f& startPoint, const Vector2f& moveDirection, const RectPhysicsCollider& otherPhysicsRect, RayVsRectInfo& out) const;
    bool PredictCollision(const CirclePhysicsCollider& other /*TODO: out needed */);
    // bool PredictCollision(const Collider& other);

    void UpdatePhysics(float elapsedTime);
    void CheckEntityCollision(const Vector2f& position, const Vector2f& velocity) const;
    virtual void CallBackHitTile(std::vector<std::pair<const Tile*, RayVsRectInfo>>& hitInfo);
    virtual void CallBackHitEntity(std::vector<std::pair<RayVsRectInfo, Entity*>>& hitInfo);
    // void SetOnCollisionStay(std::function<void()> function);
    // void RemoveOnCollisionStay();
    
    static bool RayCastCollision(const Vector2f& startPoint, const Vector2f& moveDirection, const Rectf& rect, RayVsRectInfo& out);

    /// Update
    ///
    /// Predict if we are going to hit world
    /// World tiles. Grid Collider???
    /// Need to know what tile we hit and where
    ///
    /// Predict if we hit creatures
    /// List of all creatures
    /// Tell player what enemy we hit
    ///
    /// So we are going to have collider type pass through or solid
    /// We have a callback function that gets called when we hit any other collider.
    /// If its solid the physics engine will apply normal opposite force.
    /// Otherwise it will do nothing but tell the subscriber we hit that object.
    /// 
    /// We might want onEnter, onStay, onExit. For now lets do onStay
    

private:
    Rectf m_Rect;
    Vector2f m_Velocity{};

    float m_InverseMass;
    float m_Bounciness;
    bool m_IsTurningLeft{};

    WorldManager* m_WorldManager;

    // cache vector memory so the array can be reused
    static std::vector<std::pair<const Tile*, RayVsRectInfo>> m_HitsCache;
    static std::vector<std::pair<const Tile*, RayVsRectInfo>> m_BlocksWeHit;
    static std::vector<std::pair<RayVsRectInfo, Entity*>> m_EntitiesWeHit;

};
