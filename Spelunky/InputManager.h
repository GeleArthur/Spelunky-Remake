#pragma once

class WorldManager;

class InputManager final
{
public:
    explicit InputManager(WorldManager* worldManager);
    
    const Vector2f& GetMoveInput() const;
    bool PressedJumpThisFrame() const;
    bool IsHoldingJump() const;
    bool IsHoldingSprint() const;
    bool PressedActionThisFrame() const;
    bool PressedBombThisFrame() const;
    bool PressedInteractThisFrame() const;
    bool PressingSecretCode() const;

    void Update();

private:
    Vector2f m_MoveInput{};
    bool m_HoldingJump{};
    bool m_HoldingSprint{};

    bool m_PressedJumpThisFrame{};
    bool m_PressedJumpPrevState{};
    
    bool m_PressedActionThisFrame{};
    bool m_PressedActionPrevState{};

    bool m_PressedBombThisFrame{};
    bool m_PressedBombPrevState{};

    bool m_PressedInteractThisFrame{};
    bool m_PressedInteractPrevState{};
};
