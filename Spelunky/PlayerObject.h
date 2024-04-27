﻿#pragma once
#include <vector>

#include "Entity.h"
#include "PhysicsComponent.h"
#include "PhysicsObject.h"
#include "RectPhysicsCollider.h"

class WorldManager;
class Entity;
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


class PlayerObject final : public RectPhysicsCollider, public Entity
{
public:
    explicit PlayerObject(WorldManager* worldManager);
    virtual void Draw() const override;
    virtual void Update(float elapsedTimes) override;
    void UpdateAnimationState();
    void Respawn(const Vector2f& spawnLocation);
    
    Vector2f GetPosition() const;
    virtual EntityType GetEntityType() const override;
    virtual void CallBackHitTile(std::pair<const Tile*, RayVsRectInfo> hitInfo) override;

private:
    PlayerAnimationState m_CurrentAnimation{PlayerAnimationState::idle};
    int m_AnimationFrame{};
    float m_AnimationTimer{};
    bool m_IsLookingToLeft{true};

    const float m_MaxSpeed{256.0f}; // const member is dum
    
    bool m_IsOnGround{false};
    Entity* m_PickupItem{};

    SpriteSheetManager* m_SpriteSheetManager;
    WorldManager* m_WorldManager;
};
