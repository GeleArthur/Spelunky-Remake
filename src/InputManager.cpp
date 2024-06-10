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

bool InputManager::PressedActionThisFrame() const
{
    return m_PressedActionThisFrame;
}
bool InputManager::PressedBombThisFrame() const
{
    return m_PressedBombThisFrame;
}
bool InputManager::PressedInteractThisFrame() const
{
    return m_PressedInteractThisFrame;
}
bool InputManager::PressingSecretCode() const
{
    const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
    return pStates[SDL_SCANCODE_Q] && pStates[SDL_SCANCODE_W] && pStates[SDL_SCANCODE_E] && pStates[SDL_SCANCODE_R] && pStates[SDL_SCANCODE_T] && pStates[SDL_SCANCODE_Y];
}

void InputManager::Update()
{
    const Uint8 *pStates = SDL_GetKeyboardState( nullptr );

    m_PressedJumpThisFrame = false;
    m_PressedActionThisFrame = false;
    m_PressedBombThisFrame = false;
    m_PressedInteractThisFrame = false;

    if(pStates[SDL_SCANCODE_Z] && static_cast<bool>(pStates[SDL_SCANCODE_Z]) != m_PressedJumpPrevState)
    {
        m_PressedJumpThisFrame = true;
    }
    if(pStates[SDL_SCANCODE_X] && static_cast<bool>(pStates[SDL_SCANCODE_X]) != m_PressedActionPrevState)
    {
        m_PressedActionThisFrame = true;
    }
    if(pStates[SDL_SCANCODE_A] && static_cast<bool>(pStates[SDL_SCANCODE_A]) != m_PressedBombPrevState)
    {
        m_PressedBombThisFrame = true;
    }
    if(pStates[SDL_SCANCODE_SPACE] && static_cast<bool>(pStates[SDL_SCANCODE_SPACE]) != m_PressedBombPrevState)
    {
        m_PressedInteractThisFrame = true;
    }
    

    m_PressedJumpPrevState = pStates[SDL_SCANCODE_Z];
    m_PressedActionPrevState = pStates[SDL_SCANCODE_X];
    m_PressedBombPrevState = pStates[SDL_SCANCODE_A];
    m_PressedInteractPrevState = pStates[SDL_SCANCODE_A];

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

