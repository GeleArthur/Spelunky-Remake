#pragma once

class InputManager final
{
public:
    static const Vector2f& GetMoveInput();
    static bool PressedJumpThisFrame();
    static bool IsHoldingJump();
    static bool IsHoldingSprint();
    static bool PressedGrabItemThisFrame();

    static void Update();
    static void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
    static void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
    static void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
    static void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
    static void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);
    static void ProcessWheelEvent(const SDL_MouseWheelEvent& e);

    // TODO: controllers
private:
    static Vector2f m_MoveInput;
    static bool m_HoldingJump;
    static bool m_HoldingSprint;

    static bool m_PressedJumpThisFrame;
    static bool m_PressedJumpPrevState;
    
    static bool m_PressedGrabThisFrame;
    static bool m_PressedGrabPrevState;
};
