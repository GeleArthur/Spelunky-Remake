#pragma once

class WorldManager;

class InputManager final
{
public:
    InputManager(WorldManager* worldManager);
    ~InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager& other) = delete;
    InputManager(InputManager&& other) = delete;
    InputManager& operator=(InputManager&& other) = delete;
    
    const Vector2f& GetMoveInput() const;
    bool PressedJumpThisFrame() const;
    bool IsHoldingJump() const;
    bool IsHoldingSprint() const;
    bool PressedActionThisFrame() const;
    bool PressedBombThisFrame() const;


    void Update();
    void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
    void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
    void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
    void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
    void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);
    void ProcessWheelEvent(const SDL_MouseWheelEvent& e);

    // TODO: controllers
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
};
