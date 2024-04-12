#include "pch.h"
#include "PlayerObject.h"

#include <complex>
#include <iostream>
#include <vector>

#include "CircleCollider.h"
#include "RectCollider.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Tile.h"

PlayerObject::PlayerObject(SpriteSheetManager* spriteSheetManager, const std::vector<std::vector<Tile>>* tiles):
    PhysicsObject(new RectCollider{Rectf{0, 0, 40, 63}}, tiles),
    m_AnimationFrame(0),
    m_AnimationTimer(0),
    m_SpriteSheetManager(spriteSheetManager)
{
}

void PlayerObject::Draw() const
{
    Rectf animationSource{0,0,80,80};
    
    //TODO: move hardcoded animation numbers
    switch (m_CurrentAnimation)
    {
    case PlayerAnimationState::idle:
        animationSource.left = 0;
        animationSource.top = 0;
        break;
    case PlayerAnimationState::walk:
        animationSource.top = 0;
        animationSource.left = 80.0f + static_cast<float>(m_AnimationFrame%7) * 80.0f;
        break;
    case PlayerAnimationState::inAir:
        animationSource.top = 9*80.0f;
        if(m_Velocity.y > 0 && m_Velocity.y < 5)
        {
            animationSource.left = 4*80.0f;
        }
        else if(m_Velocity.y > 5 && m_Velocity.y < 25)
        {
            animationSource.left = 5*80.0f;
        }
        else if(m_Velocity.y > 25)
        {
            animationSource.left = 7*80.0f;
        }
        break;
    case PlayerAnimationState::climbing:
        break;
    case PlayerAnimationState::hanging:
        break;
    }
    
    glPushMatrix();
    glTranslatef(GetCollider()->GetOrigin().x, GetCollider()->GetOrigin().y, 0);
    
    glScalef(1, -1, 1);
    TTF_Font* pFont = TTF_OpenFont( "arial.ttf", 16 );
    Texture(m_Velocity.ToString(), pFont, {1,1,1}).Draw();
    glScalef(1, -1, 1);
    
    if(m_Velocity.x < 0)
    {
        glScalef(-1, 1, 1);
    }
    m_SpriteSheetManager->GetCurrentPlayerTexture()->Draw(-Vector2f{40,40}, animationSource);


    
    glPopMatrix();
}

void PlayerObject::Update(const float elapsedTimes)
{
    const Uint8 *pStates = SDL_GetKeyboardState( nullptr );

    Vector2f inputVelocity{};
    if ( pStates[SDL_SCANCODE_RIGHT] || pStates[SDL_SCANCODE_D] )
    {
        inputVelocity += Vector2f{1000, 0} * elapsedTimes;
    }
    if ( pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_A] )
    {
        inputVelocity += Vector2f{-1000, 0} * elapsedTimes;
    }

    if(inputVelocity.SquaredLength() < 0.001)
    {
        inputVelocity = -m_Velocity * elapsedTimes;
    }

    m_Velocity += inputVelocity;
    
    
    const float limitedVelocity = std::min(std::abs(m_Velocity.x), 500.0f);
    if(m_Velocity.x > 0)
        m_Velocity.x = limitedVelocity;
    else
        m_Velocity.x = -limitedVelocity;
    
    UpdatePhysics(elapsedTimes);
    // std::cout <<std::boolalpha << m_IsOnGround << '\n';
    m_AnimationTimer += elapsedTimes;
    UpdateAnimationState();
}

void PlayerObject::UpdateAnimationState()
{
    const float speed = m_Velocity.SquaredLength();
    
    switch (m_CurrentAnimation)
    {
    case PlayerAnimationState::idle:
        if(m_IsOnGround == false)
        {
            m_CurrentAnimation = PlayerAnimationState::inAir;
            m_AnimationTimer = 0;
            m_AnimationFrame = 0;
        }
        else if(speed > 0.01)
        {
            m_CurrentAnimation = PlayerAnimationState::walk;
            m_AnimationTimer = 0;
            m_AnimationFrame = 0;
        }

        break;
    case PlayerAnimationState::walk:
        if(m_IsOnGround == false)
        {
            m_CurrentAnimation = PlayerAnimationState::inAir;
            m_AnimationTimer = 0;
            m_AnimationFrame = 0;
        }
        else
        {
            if(speed < 0.01)
            {
                m_CurrentAnimation = PlayerAnimationState::idle;
                m_AnimationTimer = 0;
                m_AnimationFrame = 0;
            }
            else if(speed < 1000)
            {
                if(m_AnimationTimer > 0.5f)
                {
                    m_AnimationTimer = 0;
                    m_AnimationFrame++;
                }
            }
            else
            {
                if(m_AnimationTimer > 0.1f)
                {
                    m_AnimationTimer = 0;
                    m_AnimationFrame++;
                }
            }
        }
        break;
    case PlayerAnimationState::inAir:
        if(m_IsOnGround)
        {
            m_CurrentAnimation = PlayerAnimationState::walk;
            m_AnimationTimer = 0;
            m_AnimationFrame = 0;
            return;
        }
        break;
    case PlayerAnimationState::climbing:
        break;
    case PlayerAnimationState::hanging:
        break;

    }
}

void PlayerObject::Respawn(const Vector2f& spawnLocation)
{
    GetCollider()->SetOrigin(spawnLocation);
    m_AnimationFrame = 0;
    m_AnimationTimer = 0;
}
