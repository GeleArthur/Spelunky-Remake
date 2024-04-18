#pragma once
#include <vector>

#include "PhysicsComponent.h"
#include "PhysicsObject.h"
#include "RectPhysicsCollider.h"

class WorldManager;
class Item;
class Tile;
class SpriteSheetManager;

enum class PlayerAnimationState
{
    idle,
    walk,
    inAir,
    climbing,
    hanging
};


class PlayerObject final : public PhysicsComponent
{
public:
    explicit PlayerObject(WorldManager* worldManager);
    void Draw() const;
    void Update(float elapsedTimes);
    void UpdateAnimationState();
    void Respawn(const Vector2f& spawnLocation);
    
    virtual ColliderTypes GetColliderType() const override;
    virtual Collider* GetCollider() override;

    Vector2f GetPosition() const;

private:
    PlayerAnimationState m_CurrentAnimation{PlayerAnimationState::idle};
    int m_AnimationFrame{};
    float m_AnimationTimer{};
    bool m_IsLookingToLeft{true};

    const float m_MaxSpeed{500}; // const member is dum
    bool m_IsOnGround{false};
    Item* m_PickupItem{};
    RectPhysicsCollider m_PhysicsCollider;

    SpriteSheetManager* m_SpriteSheetManager;
    WorldManager* m_WorldManager;
};
