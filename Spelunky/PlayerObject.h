#pragma once
#include <vector>

#include "PhysicsObject.h"

class Tile;
class SpriteSheetManager;

enum class PlayerAnimationState
{
    idle,
    walk,
    run,
    falling,
    climbing,
    hanging
};

class PlayerObject final : public PhysicsObject
{
public:
    explicit PlayerObject(SpriteSheetManager* spriteSheetManager, const std::vector<std::vector<Tile>>* tiles);
    void Draw() const;
    void Update(float elapsedTimes);
    void UpdateAnimationState();
    void Respawn(const Vector2f& spawnLocation);

private:
    PlayerAnimationState m_CurrentAnimation{PlayerAnimationState::idle};
    int m_AnimationFrame;
    float m_AnimationTimer;
    SpriteSheetManager* m_SpriteSheetManager;
};
