#pragma once
#include <vector>


#include "Entity.h"
#include "RectPhysicsCollider.h"

class EntityPickupRectCollider;
class InputManager;
class WorldManager;
class Entity;
class Tile;
class SpriteSheetManager;

enum class PlayerAnimationState
{
    idle,
    walk,
    crouching,
    inAir,
    hanging,
    ladderClimbing,
    wiping,
    ragdoll,
};
enum class PlayerState
{
    normal,
    hanging,
    ragdoll,
    ladderClimbing,

    dead,
    enteringLeaving
};


class PlayerObject final : public Entity
{
public:
    explicit PlayerObject(WorldManager* worldManager);
    
    virtual void Draw() const override;
    virtual void Update(float elapsedTimes) override;
    void Respawn(const Vector2f& spawnLocation);

    Vector2f GetPosition() const;
    PlayerState GetPlayerState() const;
    virtual EntityType GetEntityType() const override;
    bool CanPlayerLeave() const;

protected:

    // virtual void YouGotHit(int damage, Vector2f force, HitType hitType) override;
    virtual void YouGotHit(int damage, const Vector2f& force) override;
    
private:
    void UpdateAnimationState(float elapsedTimes);
    void ChangeAnimationState(PlayerAnimationState newAnimationState);
    void HandleWallHanging(float elapsedTimes);
    void PlayerMovement(float elapsedTimes, const Vector2f& moveInput);
    void LadderClimbing(const Vector2f& moveInput);
    void PlayerWhipping(float elapsedTimes);
    void PlayerJump();
    void LimitSpeed();
    void CheckPickUp();
    void CheckBomb() const;
    void CheckCrouching(const Vector2f& moveInput);
    void PlayerInteract();

    void TilesWeHitCheck(const std::vector<std::pair<const Tile*, RayVsRectInfo>>& hitInfo);
    void EntitiesWeHitCheck(const std::vector<std::pair<RayVsRectInfo, Entity*>>& hitInfo);

    static constexpr float WIPING_AMOUNT_TIMER{0.45f};
    
    PlayerAnimationState m_CurrentAnimation{PlayerAnimationState::idle};
    PlayerState m_PlayerState{PlayerState::normal};
    
    int m_AnimationFrame{};
    float m_AnimationTimer{};
    bool m_IsLookingToLeft{true};
    
    float m_MaxSpeed{256.0f};
    float m_MaxSprintSpeed{512};
    float m_StopSpeed{256.0f};
    float m_RagDollTimer{};
    
    float m_WipTimer{};
    bool m_WipHasHit{};

    float m_MaxCrouchingSpeed{64.0f};
    
    bool m_IsOnGround{false};
    bool m_IsJumping{false};
    bool m_IsOnLadder{false};
    bool m_IsCrouching{false};
    bool m_IsWiping{false};

    bool m_InvisibilityFrames{false};
    float m_InvisibilityTimer{0};
    float m_InvisibilityAnimationTimer{};
    
    bool m_CanLeaveCave{false};
    
    // bool m_IsHanging{false};
    bool m_IsTouchingWall{false};
    bool m_IsTouchingLeftWall{false};
    
    EntityPickupRectCollider* m_PickupItem{};

    SpriteSheetManager* m_SpriteSheetManager;
    InputManager* m_InputManager;
    WorldManager* m_WorldManager;
};
