#include "pch.h"
#include "PlayerObject.h"

#include <vector>

#include "CircleCollider.h"
#include "RectCollider.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Tile.h"

PlayerObject::PlayerObject(SpriteSheetManager* spriteSheetManager, const std::vector<std::vector<Tile>>* tiles):
     PhysicsObject(new RectCollider{Rectf{0,0,64,64}}, tiles),
    m_SpriteSheetManager(spriteSheetManager)
{
}

void PlayerObject::Draw() const
{
    // TODO: animation system

    Rectf animationSource{0,0,80,80};

    //TODO: move hardcoded animation numbers
    switch (m_CurrentAnimation)
    {
    case PlayerAnimationState::idle:
        animationSource.left = 0;
        animationSource.top = 0;
        break;
    case PlayerAnimationState::walk:
    case PlayerAnimationState::run:
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
    if ( pStates[SDL_SCANCODE_RIGHT] || pStates[SDL_SCANCODE_D] )
    {
        m_Velocity += Vector2f{10, 0};
    }
    if ( pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_A] )
    {
        m_Velocity += Vector2f{-10, 0};
    }
    if ( pStates[SDL_SCANCODE_UP] || pStates[SDL_SCANCODE_W] )
    {
        m_Velocity += Vector2f{0, -10};
    }
    if ( pStates[SDL_SCANCODE_DOWN] || pStates[SDL_SCANCODE_S] )
    {
        m_Velocity += Vector2f{0, 10};
    }
    
    UpdatePhysics(elapsedTimes);
    m_AnimationTimer += elapsedTimes;
    UpdateAnimationState();
}

void PlayerObject::UpdateAnimationState()
{
    const float speed = m_Velocity.SquaredLength();
    
    switch (m_CurrentAnimation)
    {
    case PlayerAnimationState::idle:
        if(speed > 0.01)
        {
            m_CurrentAnimation = PlayerAnimationState::walk;
            m_AnimationTimer = 0;
            m_AnimationFrame = 0;
        }
        break;
        
    case PlayerAnimationState::walk:
        if(speed < 0.01)
        {
            m_CurrentAnimation = PlayerAnimationState::idle;
            m_AnimationTimer = 0;
            m_AnimationFrame = 0;
        }
        else if(speed > 5000)
        {
            m_CurrentAnimation = PlayerAnimationState::run;
            m_AnimationTimer = 0;
            m_AnimationFrame = 0;
        }
        
        if(m_AnimationTimer > 0.1f)
        {
            m_AnimationTimer = 0;
            m_AnimationFrame++;
        }
        break;
    case PlayerAnimationState::run:
        if(speed < 5000)
        {
            m_CurrentAnimation = PlayerAnimationState::walk;
            m_AnimationTimer = 0;
            m_AnimationFrame = 0;
        }
        
        if(m_AnimationTimer > 0.05f)
        {
            m_AnimationTimer = 0;
            m_AnimationFrame++;
        }
        break;
    case PlayerAnimationState::inAir:
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
