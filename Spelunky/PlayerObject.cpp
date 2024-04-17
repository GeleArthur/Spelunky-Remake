#include "pch.h"
#include "PlayerObject.h"

#include <complex>
#include <iostream>
#include <vector>

#include "CirclePhysicsCollider.h"
#include "GizmosDrawer.h"
#include "RectPhysicsCollider.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Tile.h"
#include "WorldManager.h"

PlayerObject::PlayerObject(WorldManager* worldManager, SpriteSheetManager* spriteSheetManager, const std::vector<std::vector<Tile>>* tiles):
    m_PhysicsCollider(Rectf{0, 0, 40, 63}),
    m_SpriteSheetManager(spriteSheetManager),
    m_WorldManager(worldManager)
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
        {
            const Vector2f velocity = m_PhysicsCollider.GetVelocity();
            animationSource.top = 9*80.0f;
            if(velocity.y > 0 && velocity.y < 5)
            {
                animationSource.left = 4*80.0f;
            }
            else if(velocity.y > 5 && velocity.y < 25)
            {
                animationSource.left = 5*80.0f;
            }
            else if(velocity.y > 25)
            {
                animationSource.left = 7*80.0f;
            }
        }
        break;
    case PlayerAnimationState::climbing:
        break;
    case PlayerAnimationState::hanging:
        break;
    }
    
    glPushMatrix();
    const Vector2f position = m_PhysicsCollider.GetCenter();
    glTranslatef(position.x, position.y, 0);
    
    GizmosDrawer::SetColor({1,1,1});
    GizmosDrawer::DrawQText(position, m_PhysicsCollider.GetVelocity().ToString());
    

    if(m_IsLookingToLeft)
        glScalef(-1,1,1);
    m_SpriteSheetManager->GetCurrentPlayerTexture()->Draw(-Vector2f{40,40}, animationSource);
    
    glPopMatrix();

    if(m_PickupItem != nullptr)
    {
        m_PickupItem->Draw();
    }
}

void PlayerObject::Update(const float elapsedTimes)
{
    const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
    // 3000 as run speed maybe

    Vector2f inputVelocity{};
    if ( pStates[SDL_SCANCODE_RIGHT] || pStates[SDL_SCANCODE_D] )
    {
        inputVelocity += Vector2f{1000, 0} * elapsedTimes;
    }
    if ( pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_A] )
    {
        inputVelocity += Vector2f{-1000, 0} * elapsedTimes;
    }
    if(pStates[SDL_SCANCODE_SPACE])
    {
        if(m_IsOnGround)
        {
            inputVelocity.y -= 530;
        }
    }
    if(pStates[SDL_SCANCODE_LSHIFT])
    {
        std::vector<Item*> items = m_WorldManager->GetItemManager()->GetItems();
        for (int i{}; i < items.size(); ++i)
        {
            //TODO Test for multiple objects by distance
            if(items.at(i)->CanPickUp(GetCollider()))
            {
                m_PickupItem = items.at(i);
                m_PickupItem->SetIsPickedUp(true);
                break;
            }
        }
    }

    if(m_PickupItem != nullptr && pStates[SDL_SCANCODE_E])
    {
        m_PickupItem->SetIsPickedUp(false);
        m_PickupItem->Throw(Vector2f{m_IsLookingToLeft ? -1000.0f: 1000.0f, -200});
        m_PickupItem = nullptr;
    }

    Vector2f velocity = m_PhysicsCollider.GetVelocity();

    if(abs(inputVelocity.x) < 0.001)
    {
        float slowDownLimit = 3000.0f * elapsedTimes;// std::min(10.0f, std::abs(m_Velocity.x));
        if(slowDownLimit > std::abs(velocity.x))
            slowDownLimit = std::abs(velocity.x);
        
        if(velocity.x > 0) slowDownLimit *= -1;
        
        inputVelocity.x += slowDownLimit;
    }
    
    if(std::abs(velocity.x) < 0.1)
    {
        velocity.x = 0;
    }
    else
    {
        m_IsLookingToLeft = velocity.x < 0;
    }

    m_PhysicsCollider.ApplyForce(inputVelocity);
    
    
    const float limitedVelocity = std::min(std::abs(m_Velocity.x), m_MaxSpeed);
    if(m_Velocity.x > 0)
        m_Velocity.x = limitedVelocity;
    else
        m_Velocity.x = -limitedVelocity;
    
    m_Velocity.y = std::min(m_Velocity.y, 1000.0f);
    
    UpdatePhysics(elapsedTimes);
    if(m_PickupItem != nullptr)
    {
        m_PickupItem->Teleport(GetCollider()->GetOrigin());
    }
    
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
            else
            {
                if(m_AnimationTimer > 0.05+(1-(std::abs(m_Velocity.x)/m_MaxSpeed))*0.2)
                {
                    m_AnimationTimer = 0;
                    m_AnimationFrame++;
                }
            }
            // else if(speed < 250)
            // {
            //     if(m_AnimationTimer > 0.5f)
            //     {
            //         m_AnimationTimer = 0;
            //         m_AnimationFrame++;
            //     }
            // }
            // else
            // {
            //     if(m_AnimationTimer > 0.1f)
            //     {
            //         m_AnimationTimer = 0;
            //         m_AnimationFrame++;
            //     }
            // }
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
    m_PickupItem = nullptr;
}
