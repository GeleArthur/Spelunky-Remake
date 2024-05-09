#include "pch.h"
#include "InputManager.h"

#include "WorldManager.h"

InputManager::InputManager(WorldManager* worldManager)
{
    worldManager->SetInputManager(this);
}

const Vector2f& InputManager::GetMoveInput() const
{
    return m_MoveInput;
}

bool InputManager::PressedJumpThisFrame() const
{
    return m_PressedJumpThisFrame;
}

bool InputManager::IsHoldingJump() const
{
    return m_HoldingJump;
}

bool InputManager::IsHoldingSprint() const
{
    return m_HoldingSprint;
}

bool InputManager::PressedGrabItemThisFrame() const
{
    return m_PressedGrabThisFrame;
}

void InputManager::Update()
{
    const Uint8 *pStates = SDL_GetKeyboardState( nullptr );

    m_PressedJumpThisFrame = false;
    m_PressedGrabThisFrame = false;

    if(pStates[SDL_SCANCODE_Z] && static_cast<bool>(pStates[SDL_SCANCODE_Z]) != m_PressedJumpPrevState)
    {
        m_PressedJumpThisFrame = true;
    }

    if(pStates[SDL_SCANCODE_X] && static_cast<bool>(pStates[SDL_SCANCODE_X]) != m_PressedGrabPrevState)
    {
        m_PressedGrabThisFrame = true;
    }

    m_PressedJumpPrevState = pStates[SDL_SCANCODE_Z];
    m_PressedGrabPrevState = pStates[SDL_SCANCODE_X];

    m_HoldingJump = false;
    m_HoldingSprint = false;
    if(pStates[SDL_SCANCODE_Z])
    {
        m_HoldingJump = true;
    }
    if(pStates[SDL_SCANCODE_LSHIFT])
    {
        m_HoldingSprint = true;
    }
    
    
    m_MoveInput = Vector2f{0,0};
    if ( pStates[SDL_SCANCODE_RIGHT] )
    {
        m_MoveInput.x += 1;
    }
    if ( pStates[SDL_SCANCODE_LEFT] )
    {
        m_MoveInput.x += -1;
    }
    if ( pStates[SDL_SCANCODE_UP]  )
    {
        m_MoveInput.y += -1;
    }
    if ( pStates[SDL_SCANCODE_DOWN] )
    {
        m_MoveInput.y += 1;
    }

    

}

void InputManager::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
}

void InputManager::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
}

void InputManager::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}

void InputManager::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
}

void InputManager::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}

void InputManager::ProcessWheelEvent(const SDL_MouseWheelEvent& e)
{
}
