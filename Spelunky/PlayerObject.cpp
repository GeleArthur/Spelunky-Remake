#include "pch.h"
#include "PlayerObject.h"

#include <complex>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "CirclePhysicsCollider.h"
#include "Game.h"
#include "GizmosDrawer.h"
#include "InputManager.h"
#include "RectPhysicsCollider.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Tile.h"
#include "WorldManager.h"

PlayerObject::PlayerObject(WorldManager* worldManager):
    RectPhysicsCollider(Rectf{0, 0, 40, 56}, 60, 0.0f, worldManager),
    m_SpriteSheetManager(worldManager->GetSpriteSheet()),
    m_InputManager(worldManager->GetInputManager()),
    m_WorldManager(worldManager)
{
}

void PlayerObject::UpdateAnimationState()
{
    const Vector2f velocity = GetVelocity();
    const float speed = velocity.SquaredLength();
    
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
                if(m_AnimationTimer > 0.05+(1-(std::abs(velocity.x)/m_MaxSpeed))*0.2)
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
            const Vector2f velocity = GetVelocity();
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
    const Vector2f position = GetCenter();
    glTranslatef(position.x, position.y, 0);
    
    GizmosDrawer::SetColor({1,1,1});
    GizmosDrawer::DrawQText(position, GetVelocity().ToString());
    

    if(m_IsLookingToLeft)
        glScalef(-1,1,1);
    m_SpriteSheetManager->GetCurrentPlayerTexture()->Draw(-Vector2f{40,40}, animationSource);
    
    glPopMatrix();

    // if(m_PickupItem != nullptr)
    // {
    //     m_PickupItem->Draw();
    // }
}

void PlayerObject::Update(const float elapsedTimes)
{
    Vector2f inputVelocity{};
    const Vector2f moveInput = m_InputManager->GetMoveInput();
    
    // std::cout << Game::GetTime() << '\n';

    // std::cout << std::setw(2);

    // std::cout << moveInput.x << '\n';
    // std::cout << GetVelocity().x << '\n';

    if(moveInput.x != 0 && moveInput.x > 0 != GetVelocity().x > 0)
    {
        float SlowDownSpeed = m_MaxSpeed * elapsedTimes / 0.2f;
        float direction = GetVelocity().x > 0 ? -1 : 1;
        inputVelocity.x += direction * SlowDownSpeed;
        
        std::cout << elapsedTimes <<"\n";
    }
    
    // Accelerating
    inputVelocity += Vector2f{moveInput.x * m_MaxSpeed/0.2f * elapsedTimes, 0};
    
    
    if(m_InputManager->PressedJumpThisFrame())
    {
        if(m_IsOnGround)
        {
            SetVelocity(GetVelocity().x, -500);
        }
    }

    Vector2f velocity = GetVelocity();

    // const float limitedVelocity = std::min(std::abs(velocity.x), m_MaxSpeed);
    // if(velocity.x > 0)
    //     SetVelocity(limitedVelocity, velocity.y);
    // else
    //     SetVelocity(-limitedVelocity, velocity.y);

    // TODO: Maybe move this to physics class???
    if(std::abs(velocity.x) < 0.0001)
    {
        SetVelocity(0, velocity.y);
    }
    else
    {
        m_IsLookingToLeft = velocity.x < 0;
    }

    ApplyForce(inputVelocity);
    if(std::abs(GetVelocity().x) > m_MaxSpeed)
    {
        if(GetVelocity().x > 0)
            SetVelocity(m_MaxSpeed, GetVelocity().y);
        else
            SetVelocity(-m_MaxSpeed, GetVelocity().y);
    }

    
    ApplyForce(Vector2f{0,1000} * elapsedTimes);
    
    // SetVelocity(velocity.x, std::min(velocity.y, 1000.0f));
    m_IsOnGround = false;
    UpdatePhysics(elapsedTimes);
    
    m_AnimationTimer += elapsedTimes;
    UpdateAnimationState();
}

void PlayerObject::CallBackHitTile(std::pair<const Tile*, RayVsRectInfo> hitInfo)
{
    if(hitInfo.second.normal.y < 0)
    {
        m_IsOnGround = true;
    }
}

void PlayerObject::Respawn(const Vector2f& spawnLocation)
{
    SetCenter(spawnLocation);
    m_AnimationFrame = 0;
    m_AnimationTimer = 0;
    m_PickupItem = nullptr;
}

Vector2f PlayerObject::GetPosition() const
{
    return GetCenter();
}

EntityType PlayerObject::GetEntityType() const
{
    return EntityType::player;
}


