#pragma once
#include <vector>

#include "Entity.h"
#include "RectPhysicsCollider.h"

class InputManager;
class WorldManager;
class Entity;
class Tile;
class SpriteSheetManager;

enum class PlayerAnimationState
{
    idle,
    walk,
    inAir,
    hanging
};
enum class PlayerState
{
    normal,
    hanging,
    ragdoll,
    ladderClimbing,

    dead
};


class PlayerObject final : public RectPhysicsCollider, public Entity
{
public:
    explicit PlayerObject(WorldManager* worldManager);
    virtual ~PlayerObject() override = default;
    PlayerObject(const PlayerObject& other) = delete;
    PlayerObject& operator=(const PlayerObject& other) = delete;
    PlayerObject(PlayerObject && other) = delete;
    PlayerObject& operator=(PlayerObject&& other) = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedTimes) override;
    void UpdateAnimationState(float elapsedTimes);
    void Respawn(const Vector2f& spawnLocation);
    
    Vector2f GetPosition() const;
    PlayerState GetPlayerState() const;

    
    virtual EntityType GetEntityType() const override;
    virtual void CallBackHitTile(std::pair<const Tile*, RayVsRectInfo> hitInfo) override;

private:
    void HandleWallHanging(float elapsedTimes);

    
    PlayerAnimationState m_CurrentAnimation{PlayerAnimationState::idle};
    PlayerState m_PlayerState{PlayerState::normal};
    
    int m_AnimationFrame{};
    float m_AnimationTimer{};
    bool m_IsLookingToLeft{true};
    
    float m_MaxSpeed{256.0f};
    float m_MaxSprintSpeed{512};
    float m_StopSpeed{256.0f};
    
    bool m_IsOnGround{false};
    bool m_IsJumping{false};
    bool m_IsOnLadder{false};
    
    // bool m_IsHanging{false};
    bool m_IsTouchingWall{false};
    bool m_IsTouchingLeftWall{false};
    
    Entity* m_PickupItem{};

    SpriteSheetManager* m_SpriteSheetManager;
    InputManager* m_InputManager;
    WorldManager* m_WorldManager;
};
