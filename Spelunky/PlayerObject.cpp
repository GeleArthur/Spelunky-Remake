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
#include "magic_enum.hpp"
#include "RectPhysicsCollider.h"
#include "Rock.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Tile.h"
#include "WorldManager.h"

PlayerObject::PlayerObject(WorldManager* worldManager):
    EntityRectCollider(Rectf{0, 0, 40, 56}, 60, 0.0f, worldManager),
    m_SpriteSheetManager(worldManager->GetSpriteSheet()),
    m_InputManager(worldManager->GetInputManager()),
    m_WorldManager(worldManager)
{
}

void PlayerObject::UpdateAnimationState(const float elapsedTimes)
{
    m_AnimationTimer += elapsedTimes;
    
    switch (m_CurrentAnimation)
    {
    case PlayerAnimationState::idle:
        if(m_IsOnGround == false)
        {
            ChangeAnimationState(PlayerAnimationState::inAir);
        }
        else if(GetVelocity().SquaredLength() > 0.01)
        {
            ChangeAnimationState(PlayerAnimationState::walk);
        }
        else if(m_IsCrouching)
        {
            ChangeAnimationState(PlayerAnimationState::crouching);
        }
        break;
    case PlayerAnimationState::walk:
        if(m_IsOnGround == false)
        {
            ChangeAnimationState(PlayerAnimationState::inAir);
        }
        else if(GetVelocity().SquaredLength() < 0.01)
        {
            ChangeAnimationState(PlayerAnimationState::idle);
        }
        else if(m_IsCrouching)
        {
            ChangeAnimationState(PlayerAnimationState::crouching);
        }
        else
        {
            if(m_AnimationTimer > (m_InputManager->IsHoldingSprint() ? 0.05f : 0.06f)  )
            {
                m_AnimationTimer = 0;
                m_AnimationFrame++;
            }
        }
        break;
    case PlayerAnimationState::inAir:
        if(m_PlayerState == PlayerState::hanging)
        {
            ChangeAnimationState(PlayerAnimationState::hanging);
        }
        else if(m_IsOnGround == true)
        {
            ChangeAnimationState(PlayerAnimationState::walk);
        }
        else if(m_IsOnLadder == true)
        {
            ChangeAnimationState(PlayerAnimationState::ladderClimbing);
        }
        else
        {
            const Vector2f velocity = GetVelocity();
            if(velocity.y > 0 && velocity.y < 50)
            {
                m_AnimationFrame = 4;
            }
            else if(velocity.y > 50 && velocity.y < 200)
            {
                m_AnimationFrame = 5;
            }
            else if(velocity.y > 200)
            {
                m_AnimationFrame = 7;
            }
        }
        break;
    case PlayerAnimationState::hanging:
        if(m_PlayerState != PlayerState::hanging)
        {
            ChangeAnimationState(PlayerAnimationState::inAir);
        }
        else
        {
            if(m_AnimationTimer > 0.05)
            {
                m_AnimationFrame++;
                m_AnimationTimer = 0;
            }
        }

        break;
    case PlayerAnimationState::ladderClimbing:
        if(m_IsOnLadder == false)
        {
            ChangeAnimationState(PlayerAnimationState::inAir);
        }
        else
        {
            if(std::abs(GetVelocity().y) > 0.1f )
            {
                if(m_AnimationTimer > 0.1)
                {
                    m_AnimationFrame = (m_AnimationFrame+1)%6;
                    m_AnimationTimer = 0;
                }
            }
            else
            {
                m_AnimationFrame = 0;
            }
        }
        
        break;
    case PlayerAnimationState::crouching:
        if(m_IsCrouching == false)
        {
            ChangeAnimationState(PlayerAnimationState::walk);
        }
        else
        {
            if(std::abs(GetVelocity().x) > 0.1f )
            {
                if(m_AnimationTimer > 0.04)
                {
                    m_AnimationFrame = (m_AnimationFrame+1)%7;
                    m_AnimationTimer = 0;
                }
            }
            else
            {
                m_AnimationFrame = 3;
            }
        }
        break;
    }
}

void PlayerObject::ChangeAnimationState(const PlayerAnimationState newAnimationState)
{
    m_CurrentAnimation = newAnimationState;
    m_AnimationTimer = 0;
    m_AnimationFrame = 0;
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
            animationSource.top = 9*80.0f;
            animationSource.left = static_cast<float>(m_AnimationFrame)*80.0f;
        } 
        break;
    case PlayerAnimationState::hanging:
        animationSource.top = 3 * 80.f;
        animationSource.left = static_cast<float>(8 + std::min(m_AnimationFrame, 3)) * 80.0f;
        break;
    case PlayerAnimationState::ladderClimbing:
        animationSource.top = 6 * 80.f;
        animationSource.left = static_cast<float>(m_AnimationFrame) * 80.0f;
        break;
    case PlayerAnimationState::crouching:
        animationSource.top = 1 * 80.f;
        animationSource.left = 5 * 80.0f + static_cast<float>(m_AnimationFrame) * 80.0f;
        break;
    }

    
    glPushMatrix();
    const Vector2f position = GetCenter();
    glTranslatef(position.x, position.y, 0);
    
    GizmosDrawer::SetColor({1,1,1});
    GizmosDrawer::DrawQText(position + Vector2f{0, 50}, GetVelocity().ToString());

    // std::stringstream yes;
    // yes << "IsTouchingWall: " << std::boolalpha << std::to_string(m_IsTouchingWall) << " IsLeft: " + std::to_string(m_IsTouchingLeftWall);

    // GizmosDrawer::DrawQText(position + Vector2f{0, 30}, yes.str());

    if(m_IsLookingToLeft)
        glScalef(-1,1,1);
    m_SpriteSheetManager->GetCurrentPlayerTexture()->Draw(-Vector2f{40,40}, animationSource);
    
    glPopMatrix();

    if(m_PickupItem != nullptr)
    {
        m_PickupItem->DrawPickedUp();
    }
}

void PlayerObject::Update(const float elapsedTimes)
{
    Vector2f inputVelocity{};
    const Vector2f& moveInput = m_InputManager->GetMoveInput();

    // Check is need to hang on wall
    if(m_PlayerState == PlayerState::normal)
    {
        HandleWallHanging(elapsedTimes);
    }

    // Apply normal movement input
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

    // Apply ladder climing input
    if(m_PlayerState == PlayerState::ladderClimbing)
    {
        SetVelocity(0, moveInput.y * spelucky_settings::g_TileSize*3);

        const int direction = moveInput.y > 0 ? 1 : -1;
        Vector2i newLadderTile{(GetCenter() - Vector2f{0, static_cast<float>(direction * spelucky_settings::g_TileSize/2)}) / spelucky_settings::g_TileSize};
        newLadderTile.y += direction;
        
        const TileTypes topTileType = m_WorldManager->GetCave()->GetTile(newLadderTile.x, newLadderTile.y).GetTileType();
        if(topTileType == TileTypes::air)
        {
            SetVelocity(0,0);
        }
        
        if(m_IsOnLadder == false)
        {
            m_PlayerState = PlayerState::normal;
        }
    }

    m_IsCrouching = false;
    if(m_PlayerState == PlayerState::normal && m_IsOnGround && !m_IsOnLadder)
    {
        if(moveInput.y > 0.1)
        {
            m_IsCrouching = true;
        }
    }

    // Check jumping
    if(m_PlayerState != PlayerState::ragdoll)
    {
        if(m_InputManager->PressedJumpThisFrame())
        {
            if(m_IsOnGround || m_PlayerState == PlayerState::hanging || m_PlayerState == PlayerState::ladderClimbing)
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

    // Apply gravity
    if(m_PlayerState != PlayerState::hanging && m_PlayerState != PlayerState::ladderClimbing)
    {
        ApplyForce(Vector2f{0,2048} * elapsedTimes);
    }

    // Set the x velocity to 0 if really small
    if(std::abs(GetVelocity().x) < 0.0001)
    {
        SetVelocity(0, GetVelocity().y);
    }
    else
    {
        // Set looking left
        m_IsLookingToLeft = GetVelocity().x < 0;
    }
    
    // Limit left/right speed
    float currentMaxSpeed;
    if(m_IsCrouching)
    {
        currentMaxSpeed = m_MaxCrouchingSpeed;
    }
    else
    {
        currentMaxSpeed = m_InputManager->IsHoldingSprint() ? m_MaxSprintSpeed : m_MaxSpeed;
    }
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


    // Setup varibles for UpdatePhysics
    m_IsOnGround = false;
    m_IsOnLadder = false;
    if(m_IsTouchingWall && m_PlayerState != PlayerState::hanging)
    {
        if(std::abs(moveInput.x) > 0)
        {
            m_IsTouchingWall = false;
        }
    }

    if(m_PickupItem != nullptr)
    {
        if(m_InputManager->PressedGrabItemThisFrame())
        {
            m_PickupItem->Throw(Vector2f{m_IsLookingToLeft ? -1500.0f : 1500.0f, -300.0f});
            m_PickupItem = nullptr;
        }
    }
    
    UpdatePhysics(elapsedTimes);
    UpdateAnimationState(elapsedTimes);

    if(m_PickupItem != nullptr)
    {
        // m_PickupItem->SetTargetPosition(GetCenter() + Vector2f{m_IsLookingToLeft ? -20.0f : 20.0f, 10});
        m_PickupItem->SetTargetPosition(GetCenter(), GetCenter() + Vector2f{m_IsLookingToLeft ? 20.0f : -20.0f, -10});
    }
}

void PlayerObject::CallBackHitTile(std::vector<std::pair<const Tile*, RayVsRectInfo>>& hitInfo)
{
    for (int i{}; i < hitInfo.size(); ++i)
    {
        switch (hitInfo[i].first->GetTileType())
        {
        case TileTypes::ground:
        case TileTypes::border:
            if(hitInfo[i].second.normal.y < 0)
            {
                m_IsOnGround = true;
            }
            if(hitInfo[i].second.normal.x != 0)
            {
                m_IsTouchingWall = true;
                m_IsTouchingLeftWall = hitInfo[i].second.normal.x > 0;
            }
            break;
        case TileTypes::spikes:
            if(GetVelocity().y > 0)
            {
                m_PlayerState = PlayerState::dead;
            }
            break;

        case TileTypes::ladder:
        case TileTypes::ladderTop:
            if(m_PlayerState == PlayerState::ladderClimbing && m_IsOnLadder == false)
            {
                m_IsOnLadder = true;
            }
            else if(m_PlayerState != PlayerState::ladderClimbing && m_InputManager->GetMoveInput().y < 0 && m_IsJumping == false)
            {
                if((hitInfo[i].first->GetCenter() - GetCenter()).SquaredLength() < (spelucky_settings::g_TileSize/2.0f)*(spelucky_settings::g_TileSize/2.0f))
                {
                    m_PlayerState = PlayerState::ladderClimbing;
                    m_IsTouchingWall = false;
                    m_IsOnLadder = true;
                    SetCenter(Vector2f{hitInfo[i].first->GetCenter().x, GetPosition().y});
                    SetVelocity(0,0);
                }
            }
            break;
        case TileTypes::air:
        case TileTypes::pushBlock:
        case TileTypes::entrance:
        case TileTypes::exit:
        case TileTypes::unknown:
            break;
        }
    }
}

void PlayerObject::CallBackHitEntity(std::vector<std::pair<RayVsRectInfo, Entity*>>& hitInfo)
{
    for (int i{}; i < hitInfo.size(); ++i)
    {
        switch (hitInfo[i].second->GetEntityType())
        {
        case EntityType::player:
            break;
        case EntityType::rock:
            {
                if(m_IsCrouching && m_InputManager->PressedGrabItemThisFrame() && m_PickupItem == nullptr)
                {
                    Rock* rock = dynamic_cast<Rock*>(hitInfo[i].second);

                    rock->TryToPickUp(this);
                    rock->SetTargetPosition(GetCenter(), GetCenter() + Vector2f{m_IsLookingToLeft ? 20.0f : -20.0f, -10});
                    m_PickupItem = rock;
                    return;
                }
            }
            break;
        case EntityType::arrow:
            break;
        case EntityType::snake:
            break;
        }
    }
}

void PlayerObject::HandleWallHanging(const float elapsedTimes)
{
    if(m_IsTouchingWall && !(m_InputManager->GetMoveInput().y > 0))
    {
        if(m_IsJumping == false)
        {
            const float characterTopHeight = GetRect().top ;
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
                    m_PlayerState = PlayerState::hanging;
                    SetVelocity(0, 0);
                    SetRect(Rectf{GetRect().left, float(currentTileIndex.y+1) * spelucky_settings::g_TileSize, GetRect().width, GetRect().height});
                }
            }
        }
    }
}

void PlayerObject::Respawn(const Vector2f& spawnLocation)
{
    SetCenter(spawnLocation);
    m_AnimationFrame = 0;
    m_AnimationTimer = 0;
    m_PickupItem = nullptr;
    m_PlayerState = PlayerState::normal;
}

Vector2f PlayerObject::GetPosition() const
{
    return GetCenter();
}

PlayerState PlayerObject::GetPlayerState() const
{
    return m_PlayerState;
}

EntityType PlayerObject::GetEntityType() const
{
    return EntityType::player;
}

ColliderTypes PlayerObject::GetColliderType() const
{
    return RectPhysicsCollider::GetColliderType();
}
