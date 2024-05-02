#include "pch.h"
#include "PlayerObject.h"

#include <complex>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "Cave.h"
#include "CirclePhysicsCollider.h"
#include "Game.h"
#include "GizmosDrawer.h"
#include "GlobalValues.h"
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
            if(velocity.y > 0 && velocity.y < 50)
            {
                animationSource.left = 4*80.0f;
            }
            else if(velocity.y > 50 && velocity.y < 200)
            {
                animationSource.left = 5*80.0f;
            }
            else if(velocity.y > 200)
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

    std::stringstream yes;
    yes << "IsTouchingWall: " << std::boolalpha << std::to_string(m_IsTouchingWall) << " IsLeft: " + std::to_string(m_IsTouchingLeftWall);

    GizmosDrawer::DrawQText(position + Vector2f{0, 30}, yes.str());
    

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
    const Vector2f& moveInput = m_InputManager->GetMoveInput();

    if(m_PlayerState == PlayerState::normal)
    {
        if(m_IsTouchingWall)
        {
            if(GetVelocity().y > 0)
            {
                const float characterTopHeight = GetRect().top;
                const float characterNewTopHeight = GetRect().top + GetVelocity().y * elapsedTimes;

                const int characterTileY = int(characterTopHeight / spelucky_settings::g_TileSize);
                const int characterNewTileY = int(characterNewTopHeight / spelucky_settings::g_TileSize);
                
                if(characterTileY != characterNewTileY)
                {
                    const Vector2i currentTileIndex{int(GetPosition().x / spelucky_settings::g_TileSize), characterTileY};
                    const Vector2i hangingDirection = m_IsTouchingLeftWall ? Vector2i{-1, 0} : Vector2i{1, 0};
                    
                    Cave* cave = m_WorldManager->GetCave();
                    if (cave->GetTile(currentTileIndex.x + hangingDirection.x, currentTileIndex.y).GetTileType() == TileTypes::air &&
                        cave->GetTile(currentTileIndex.x + hangingDirection.x, currentTileIndex.y + 1).GetTileType() == TileTypes::ground
                    )
                    {
                        // GizmosDrawer::DrawRect(Rectf{float(currentTileIndex.x) * spelucky_settings::g_TileSize, float(currentTileIndex.y) * spelucky_settings::g_TileSize,spelucky_settings::g_TileSize, spelucky_settings::g_TileSize}, 3);
                        // m_IsHanging = true;
                        m_PlayerState = PlayerState::hanging;
                        SetVelocity(0, 0);
                        SetRect(Rectf{GetRect().left, float(currentTileIndex.y+1) * spelucky_settings::g_TileSize, GetRect().width, GetRect().height});
                        // SetCenter(Vector2f{GetCenter().x, float(currentTileIndex.y+1) * spelucky_settings::g_TileSize});
                    }
                }
            }
        }
    }

    if(m_PlayerState == PlayerState::normal)
    {
        // No player input
        if(std::abs(moveInput.x) < 0.1f)
        {
            float slowDownSpeed = m_StopSpeed * elapsedTimes / 0.1f;
            const float overShooting = std::abs(GetVelocity().x) - slowDownSpeed;
            if(overShooting < 0)
            {
                slowDownSpeed += overShooting;
            }
            
            const float direction = GetVelocity().x > 0 ? -1.f : 1.f;
            inputVelocity.x += direction * slowDownSpeed;
        }

        // DeAcceleration to help the player turn
        if(std::abs(moveInput.x) > 0.1f && moveInput.x > 0 != GetVelocity().x > 0)
        {
            const float slowDownSpeed = m_StopSpeed * elapsedTimes / 0.1f;
            const float direction = GetVelocity().x > 0 ? -1.f : 1.f;
            inputVelocity.x += direction * slowDownSpeed;
        }
        
        // Accelerating
        
        inputVelocity += Vector2f{moveInput.x * m_MaxSpeed/0.2f * elapsedTimes, 0};
        ApplyForce(inputVelocity);
    }


    // If full jump reach top in 0.3 sec or 0.31
    // Full jump 1.5 blocks high.
    // Get to the ground in 0.26666 sec
    // Dropping 1 block takes 0.25 sec
    // Dropping 2 blocks takes 0.36 sec
    // Dropping 3 blocks takes 0.42 sec
    // Dropping 4 blocks takes 0.5 sec

    if(m_PlayerState != PlayerState::ragdoll)
    {
        if(m_InputManager->PressedJumpThisFrame())
        {
            if(m_IsOnGround || m_PlayerState == PlayerState::hanging)
            {
                m_IsJumping = true;
                m_PlayerState = PlayerState::normal;
                SetVelocity(GetVelocity().x, -630);
            }
        }
        
        if(m_IsJumping)
        {
            if(m_InputManager->IsHoldingJump() == false)
            {
                ApplyForce(Vector2f{0, -GetVelocity().y * 0.7f});
                m_IsJumping = false;
            }
            
            if(GetVelocity().y >= 0)
            {
                m_IsJumping = false;
            }
        }
    }


    if(m_PlayerState != PlayerState::hanging)
    {
        ApplyForce(Vector2f{0,2048} * elapsedTimes);
    }
    
    if(std::abs(GetVelocity().x) < 0.0001)
    {
        SetVelocity(0, GetVelocity().y);
    }
    else
    {
        m_IsLookingToLeft = GetVelocity().x < 0;
    }
    
    // Limit left/right speed
    const float currentMaxSpeed = m_InputManager->IsHoldingSprint() ? m_MaxSprintSpeed : m_MaxSpeed;
    if(std::abs(GetVelocity().x) > currentMaxSpeed)
    {
        if(GetVelocity().x > 0)
            SetVelocity(currentMaxSpeed, GetVelocity().y);
        else
            SetVelocity(-currentMaxSpeed, GetVelocity().y);
    }

    // Limit falling/up speed
    if(std::abs(GetVelocity().y) > 960)
    {
        if(GetVelocity().y > 0)
            SetVelocity(GetVelocity().x, 960);
        else
            SetVelocity(GetVelocity().x, -960);
    }

    
    m_IsOnGround = false;
    if(m_IsTouchingWall && m_PlayerState != PlayerState::hanging)
    {
        if(std::abs(moveInput.x) > 0)
        {
            m_IsTouchingWall = false;
        }
    }
    
    UpdatePhysics(elapsedTimes);
    
    m_AnimationTimer += elapsedTimes;
    UpdateAnimationState();
}

void PlayerObject::CallBackHitTile(std::pair<const Tile*, RayVsRectInfo> hitInfo)
{
    if( hitInfo.first->GetTileType() == TileTypes::ground)
    {
        if(hitInfo.second.normal.y < 0)
        {
            m_IsOnGround = true;
        }
        if(hitInfo.second.normal.x != 0)
        {
            m_IsTouchingWall = true;
            m_IsTouchingLeftWall = hitInfo.second.normal.x > 0;
        }
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


