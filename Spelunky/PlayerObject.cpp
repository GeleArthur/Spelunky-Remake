#include "pch.h"
#include "PlayerObject.h"

#include <complex>
#include <vector>
#include <algorithm>

#include "Bomb.h"
#include "Cave.h"
#include "EntityManager.h"

#include "Game.h"

#include "InputManager.h"
#include "RectPhysicsCollider.h"
#include "SoundManager.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Tile.h"
#include "WorldManager.h"

enum class PlayerAnimationState
{
    idle,
    walk,
    crouching,
    inAir,
    hanging,
    ladderClimbing,
    wiping,
    ragdoll,
};

PlayerObject::PlayerObject(WorldManager* worldManager):
    Entity(Rectf{0, 0, 40, 56}, 4, 60, 0.0f, false, worldManager),
    m_CurrentAnimation(PlayerAnimationState::idle),
    m_SpriteSheetManager(worldManager->GetSpriteSheet()),
    m_InputManager(worldManager->GetInputManager()),
    m_WorldManager(worldManager)
{
    worldManager->SetPlayer(this);
}

void PlayerObject::Draw() const
{
    if(m_InvisibilityFrames)
    {
        if(static_cast<int>(std::floor(static_cast<int>(m_InvisibilityAnimationTimer * 1.0f / 0.2f) % 2)) == 0)
        {
            return;
        }
    }
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
        animationSource.left = static_cast<float>(m_AnimationFrame)*80.0f;
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
    case PlayerAnimationState::wiping:
        animationSource.top = 4 * 80.f;
        animationSource.left = static_cast<float>(m_AnimationFrame) * 80.0f;
        break;
    case PlayerAnimationState::ragdoll:
        if(m_PhysicsCollider.GetVelocity().SquaredLength() < 100)
        {
            animationSource.top = 0 * 80.f;
            animationSource.left = 9 * 80.0f;
        }
        else
        {
            animationSource.top = 2 * 80.f;
            animationSource.left = static_cast<float>(m_AnimationFrame) * 80.0f;
        }
        break;
    }
    
    
    glPushMatrix();
    const Vector2f position = GetCenter();
    glTranslatef(position.x, position.y, 0);

    if(m_IsLookingToLeft)
        glScalef(-1,1,1);
    
    if(m_IsWiping && m_AnimationTimer < (WIPING_AMOUNT_TIMER/11.0f)*5.0f)
    {
        const float animationFrame = std::floor(m_AnimationTimer / (WIPING_AMOUNT_TIMER/11.0f));
        m_SpriteSheetManager->GetItemsTexture()->Draw(Vector2f{-40,-60}, Rectf{80*3 + animationFrame*80.0f, 80*5, 80, 80});
    }

    m_SpriteSheetManager->GetCurrentPlayerTexture()->Draw(Vector2f{-40,-40}, animationSource);

    if(m_IsWiping && m_AnimationTimer > (WIPING_AMOUNT_TIMER/11.0f)*5.0f)
    {
        const float animationFrame = std::floor(m_AnimationTimer / (WIPING_AMOUNT_TIMER/11.0f));
        m_SpriteSheetManager->GetItemsTexture()->Draw(Vector2f{-40 + 45,-35}, Rectf{80*3 + animationFrame*80.0f, 80*5, 80, 80});
    }
    
    glPopMatrix();

    if(m_PickupItem != nullptr)
    {
        m_PickupItem->Draw();
    }
}
void PlayerObject::Update(const float elapsedTimes)
{
    const Vector2f& moveInput = m_InputManager->GetMoveInput();

    if(m_PlayerState == PlayerState::normal)
    {
        HandleWallHanging(elapsedTimes);
        PlayerMovement(elapsedTimes, moveInput);
        PlayerWhipping(elapsedTimes);
        PlayerInteract();
    }
    
    CheckCrouching(moveInput);

    if(m_PlayerState == PlayerState::ladderClimbing)
    {
        LadderClimbing(moveInput);
    }
    
    // Check jumping
    if(m_PlayerState != PlayerState::ragdoll)
    {
        PlayerJump();
    }
    
    // Apply gravity
    if(m_PlayerState != PlayerState::hanging && m_PlayerState != PlayerState::ladderClimbing)
    {
        m_PhysicsCollider.ApplyForce(Vector2f{0,2048} * elapsedTimes);
    }

    if(m_PlayerState != PlayerState::ragdoll)
    {
        LimitSpeed();
        CheckPickUp();
        CheckBomb();
    }
    
    // Set the x velocity to 0 if minuscule
    if(std::abs(m_PhysicsCollider.GetVelocity().x) < 0.0001)
    {
        m_PhysicsCollider.SetVelocity(0, m_PhysicsCollider.GetVelocity().y);
    }
    else
    {
        if(m_IsWiping == false)
        {
            m_IsLookingToLeft = m_PhysicsCollider.GetVelocity().x < 0;
        }
    }

    if(m_PlayerState == PlayerState::ragdoll)
    {
        if(m_IsOnGround)
        {
            const Vector2f& velocity = m_PhysicsCollider.GetVelocity();
            Vector2f newVelocity{
                std::max(std::abs(velocity.x) * 0.7f - 0.2f, 0.0f) * (velocity.x >= 0 ? 1.0f : -1.0f),
                std::max(std::abs(velocity.y) * 0.7f - 0.2f, 0.0f) * (velocity.y >= 0 ? 1.0f : -1.0f)
            };
        
            m_PhysicsCollider.SetVelocity(newVelocity);
            
            if(m_PhysicsCollider.GetVelocity().SquaredLength() < 100)
            {
                m_RagDollTimer -= elapsedTimes;
                if(m_RagDollTimer < 0)
                {
                    m_PlayerState = PlayerState::normal;
                    m_PhysicsCollider.SetBounciness(0);
                }
            }
            else
            {
                m_RagDollTimer = 0.5f;
            }
        }
    }

    if(m_InvisibilityFrames)
    {
        m_InvisibilityAnimationTimer += elapsedTimes;
        if(m_PlayerState != PlayerState::ragdoll)
        {
            m_InvisibilityTimer -= elapsedTimes;
            if(m_InvisibilityTimer < 0)
            {
                m_InvisibilityFrames = false;
            }
        }
    }
    
    
    m_PhysicsCollider.UpdatePhysics(elapsedTimes);

    m_IsOnGround = false;
    m_IsOnLadder = false;
    m_CanLeaveCave = false;
    if(m_IsTouchingWall && m_PlayerState != PlayerState::hanging)
    {
        if(std::abs(moveInput.x) > 0)
        {
            m_IsTouchingWall = false;
        }
    }
    
    TilesWeHitCheck(m_PhysicsCollider.GetTilesWeHit());
    EntitiesWeHitCheck(m_PhysicsCollider.GetEntitiesWeHit());
    
    UpdateAnimationState(elapsedTimes);
    
    if(m_PickupItem != nullptr)
    {
        m_PickupItem->SetTargetPosition(GetCenter(), GetCenter() + Vector2f{m_IsLookingToLeft ? -m_PickupItem->GetRect().width/2.0f : m_PickupItem->GetRect().width/2.0f, 1});
    }
    
    if(m_IsOnGround == true && m_PrevIsOnGround != m_IsOnGround)
    {
        if(m_PlayerState != PlayerState::ragdoll || m_PhysicsCollider.GetVelocity().y <= -25)
        {
            m_SoundManager->PlaySoundEffect(SoundEffectTypes::land);
        }
        
    }
    m_PrevIsOnGround = m_IsOnGround;
}

void PlayerObject::TilesWeHitCheck(const std::vector<std::pair<const Tile*, RayVsRectInfo>>& hitInfo)
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
            if(m_PhysicsCollider.GetVelocity().y > 0)
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
                if((hitInfo[i].first->GetCenter() - GetCenter()).SquaredLength() < (Game::TILE_SIZE/2.0f)*(Game::TILE_SIZE/2.0f))
                {
                    m_PlayerState = PlayerState::ladderClimbing;
                    m_IsTouchingWall = false;
                    m_IsOnLadder = true;
                    m_IsWiping = false;
                    m_PhysicsCollider.SetCenter(Vector2f{hitInfo[i].first->GetCenter().x, GetPosition().y});
                    m_PhysicsCollider.SetVelocity(0,0);
                }
            }
            break;
        case TileTypes::exit:
            m_CanLeaveCave = true;
            break;

        case TileTypes::air:
        case TileTypes::pushBlock:
        case TileTypes::entrance:
        case TileTypes::unknown:
            break;
        }
    }
}
void PlayerObject::EntitiesWeHitCheck(const std::vector<std::pair<RayVsRectInfo, Entity*>>& hitInfo)
{
    for (int i{}; i < hitInfo.size(); ++i)
    {
        switch (hitInfo[i].second->GetEntityType())
        {
        case EntityType::damsel:
        case EntityType::rock:
            {
                if(m_IsCrouching && m_InputManager->PressedActionThisFrame() && m_PickupItem == nullptr)
                {
                    Entity* rock = hitInfo[i].second;

                    if(rock->TryToPickUp(this))
                    {
                        m_SoundManager->PlaySoundEffect(SoundEffectTypes::pickup);
                        rock->SetTargetPosition(GetCenter(), GetCenter() + Vector2f{m_IsLookingToLeft ? 20.0f : -20.0f, -10});
                        m_PickupItem = rock;
                        return;
                    }
                }
            }
            break;

        case EntityType::snake:
        case EntityType::bat:
        case EntityType::player:
        case EntityType::arrow:
        case EntityType::bomb:
            break;
        }
    }
}

void PlayerObject::UpdateAnimationState(const float elapsedTimes)
{
    m_AnimationTimer += elapsedTimes;

    switch (m_CurrentAnimation)
    {
    case PlayerAnimationState::idle:
        if (m_IsOnGround == false)
        {
            ChangeAnimationState(PlayerAnimationState::inAir);
        }
        else if (m_PhysicsCollider.GetVelocity().SquaredLength() > 0.01)
        {
            ChangeAnimationState(PlayerAnimationState::walk);
        }
        else if (m_IsCrouching)
        {
            ChangeAnimationState(PlayerAnimationState::crouching);
        }
        else if(m_IsWiping)
        {
            ChangeAnimationState(PlayerAnimationState::wiping);
        }
        break;
    case PlayerAnimationState::walk:
        if (m_IsOnGround == false)
        {
            ChangeAnimationState(PlayerAnimationState::inAir);
        }
        else if (m_PhysicsCollider.GetVelocity().SquaredLength() < 0.01)
        {
            ChangeAnimationState(PlayerAnimationState::idle);
        }
        else if (m_IsCrouching)
        {
            ChangeAnimationState(PlayerAnimationState::crouching);
        }
        else if(m_IsWiping)
        {
            ChangeAnimationState(PlayerAnimationState::wiping);
        }
        else
        {
            if (m_AnimationTimer > (m_InputManager->IsHoldingSprint() ? 0.05f : 0.06f))
            {
                m_AnimationTimer = 0;
                m_AnimationFrame++;
            }
        }
        break;
    case PlayerAnimationState::inAir:
        if (m_PlayerState == PlayerState::hanging)
        {
            ChangeAnimationState(PlayerAnimationState::hanging);
        }
        else if (m_IsOnGround == true)
        {
            ChangeAnimationState(PlayerAnimationState::walk);
        }
        else if (m_IsOnLadder == true)
        {
            ChangeAnimationState(PlayerAnimationState::ladderClimbing);
        }
        else if(m_IsWiping)
        {
            ChangeAnimationState(PlayerAnimationState::wiping);
        }
        else
        {
            const Vector2f& velocity = m_PhysicsCollider.GetVelocity();
            if (velocity.y > 0 && velocity.y < 50)
            {
                m_AnimationFrame = 4;
            }
            else if (velocity.y > 50 && velocity.y < 200)
            {
                m_AnimationFrame = 5;
            }
            else if (velocity.y > 200)
            {
                m_AnimationFrame = 7;
            }
        }
        break;
    case PlayerAnimationState::hanging:
        if (m_PlayerState != PlayerState::hanging)
        {
            ChangeAnimationState(PlayerAnimationState::inAir);
        }
        else
        {
            if (m_AnimationTimer > 0.05)
            {
                m_AnimationFrame++;
                m_AnimationTimer = 0;
            }
        }

        break;
    case PlayerAnimationState::ladderClimbing:
        if (m_IsOnLadder == false)
        {
            ChangeAnimationState(PlayerAnimationState::inAir);
        }
        else
        {
            if (std::abs(m_PhysicsCollider.GetVelocity().y) > 0.1f)
            {
                if (m_AnimationTimer > 0.1)
                {
                    m_AnimationFrame = (m_AnimationFrame + 1) % 6;
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
        if (m_IsCrouching == false)
        {
            ChangeAnimationState(PlayerAnimationState::walk);
        }
        else
        {
            if (std::abs(m_PhysicsCollider.GetVelocity().x) > 0.1f)
            {
                if (m_AnimationTimer > 0.04)
                {
                    m_AnimationFrame = (m_AnimationFrame + 1) % 7;
                    m_AnimationTimer = 0;
                }
            }
            else
            {
                m_AnimationFrame = 3;
            }
        }
        break;
    case PlayerAnimationState::ragdoll:
        if (m_PlayerState != PlayerState::ragdoll)
        {
            ChangeAnimationState(PlayerAnimationState::idle);
        }
        break;
    case PlayerAnimationState::wiping:
        if(m_PlayerState != PlayerState::normal)
        {
            ChangeAnimationState(PlayerAnimationState::walk);
        }
        else
        {
            if (m_AnimationTimer > WIPING_AMOUNT_TIMER)
            {
                ChangeAnimationState(PlayerAnimationState::walk);
            }
            else
            {
                m_AnimationFrame = static_cast<int>(m_AnimationTimer / (WIPING_AMOUNT_TIMER/6.0f));
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

void PlayerObject::PlayerMovement(const float elapsedTimes, const Vector2f& moveInput)
{
    Vector2f inputVelocity{};

    // No player input
    if(std::abs(moveInput.x) < 0.1f)
    {
        float slowDownSpeed = STOP_SPEED * elapsedTimes / 0.1f;
        const float overShooting = std::abs(m_PhysicsCollider.GetVelocity().x) - slowDownSpeed;
        if(overShooting < 0)
        {
            slowDownSpeed += overShooting;
        }
            
        const float direction = m_PhysicsCollider.GetVelocity().x > 0 ? -1.f : 1.f;
        inputVelocity.x += direction * slowDownSpeed;
    }

    // DeAcceleration to help the player turn
    if(std::abs(moveInput.x) > 0.1f && moveInput.x > 0 != m_PhysicsCollider.GetVelocity().x > 0)
    {
        const float slowDownSpeed = STOP_SPEED * elapsedTimes / 0.1f;
        const float direction = m_PhysicsCollider.GetVelocity().x > 0 ? -1.f : 1.f;
        inputVelocity.x += direction * slowDownSpeed;
    }
        
    // Accelerating
    inputVelocity += Vector2f{moveInput.x * MAX_SPEED/0.2f * elapsedTimes, 0};
    m_PhysicsCollider.ApplyForce(inputVelocity);
}

void PlayerObject::LadderClimbing(const Vector2f& moveInput)
{
    m_PhysicsCollider.SetVelocity(0, moveInput.y * Game::TILE_SIZE*3);

    const int direction = moveInput.y > 0 ? 1 : -1;
    Vector2i newLadderTile{(GetCenter() - Vector2f{0, static_cast<float>(direction * Game::TILE_SIZE/2)}) / Game::TILE_SIZE};
    newLadderTile.y += direction;
        
    const TileTypes topTileType = m_WorldManager->GetCave()->GetTile(newLadderTile.x, newLadderTile.y).GetTileType();
    if(topTileType == TileTypes::air)
    {
        m_PhysicsCollider.SetVelocity(0,0);
    }
        
    if(m_IsOnLadder == false)
    {
        m_PlayerState = PlayerState::normal;
    }
}

void PlayerObject::PlayerWhipping(const float elapsedTimes)
{
    if(m_InputManager->PressedActionThisFrame() && m_PickupItem == nullptr && m_IsCrouching == false)
    {
        if(m_IsWiping == false)
        {
            m_SoundManager->PlaySoundEffect(SoundEffectTypes::whip);
            m_IsWiping = true;
            m_WipHasHit = false;
            m_WipTimer = WIPING_AMOUNT_TIMER;
        }
    }
    if(m_IsWiping)
    {
        m_WipTimer -= elapsedTimes;

        if(m_WipHasHit == false && m_WipTimer < 5*WIPING_AMOUNT_TIMER/11.0f)
        {
            const std::vector<Entity*>& entities = m_WorldManager->GetEntityManager()->GetAllEntities();
            for (int i = 0; i < entities.size(); ++i)
            {
                if((entities)[i] == this) continue;
                if((entities)[i]->IsDead()) continue;
                
                RayVsRectInfo out;
                if(RectPhysicsCollider::RayCastCollision(GetPosition() + Vector2f{0, 0}, Vector2f{80.0f * (m_IsLookingToLeft?-1.0f:1.0f), 0}, (entities)[i]->GetRect(), out))
                {
                    (entities)[i]->YouGotHit(1, Vector2f{m_IsLookingToLeft? -300.0f: 300.0f, -300});
                    m_WipHasHit = true;
                }
            }
            
        }
        
        if(m_WipTimer <= 0)
        {
            m_IsWiping = false;
        }
        
    }

}

void PlayerObject::PlayerJump()
{
    if(m_InputManager->PressedJumpThisFrame())
    {
        if(m_IsOnGround || m_PlayerState == PlayerState::hanging || m_PlayerState == PlayerState::ladderClimbing)
        {
            m_IsJumping = true;
            m_PlayerState = PlayerState::normal;
            m_PhysicsCollider.SetVelocity(m_PhysicsCollider.GetVelocity().x, -630);
        }
    }
        
    if(m_IsJumping)
    {
        if(m_InputManager->IsHoldingJump() == false)
        {
            m_PhysicsCollider.ApplyForce(Vector2f{0, -m_PhysicsCollider.GetVelocity().y * 0.7f});
            m_IsJumping = false;
        }
            
        if(m_PhysicsCollider.GetVelocity().y >= 0)
        {
            m_IsJumping = false;
        }
    }
}

void PlayerObject::LimitSpeed()
{
    // Limit left/right speed
    float currentMaxSpeed;
    if(m_IsCrouching)
    {
        currentMaxSpeed = MAX_CROUCHING_SPEED;
    }
    else
    {
        currentMaxSpeed = m_InputManager->IsHoldingSprint() ? MAX_SPRINT_SPEED : MAX_SPEED;
    }
    if(std::abs(m_PhysicsCollider.GetVelocity().x) > currentMaxSpeed)
    {
        if(m_PhysicsCollider.GetVelocity().x > 0)
            m_PhysicsCollider.SetVelocity(currentMaxSpeed, m_PhysicsCollider.GetVelocity().y);
        else
            m_PhysicsCollider.SetVelocity(-currentMaxSpeed, m_PhysicsCollider.GetVelocity().y);
    }

    // Limit falling/up speed
    if(std::abs(m_PhysicsCollider.GetVelocity().y) > 960)
    {
        if(m_PhysicsCollider.GetVelocity().y > 0)
            m_PhysicsCollider.SetVelocity(m_PhysicsCollider.GetVelocity().x, 960);
        else
            m_PhysicsCollider.SetVelocity(m_PhysicsCollider.GetVelocity().x, -960);
    }
}
void PlayerObject::CheckPickUp()
{
    if(m_PickupItem != nullptr)
    {
        if(m_InputManager->PressedActionThisFrame())
        {
            if(m_IsCrouching)
            {
                m_SoundManager->PlaySoundEffect(SoundEffectTypes::dropItem);
                m_PickupItem->Throw(Vector2f{m_IsLookingToLeft ? -300.0f : 300.0f, -10.0f});
            }
            else
            {
                m_SoundManager->PlaySoundEffect(SoundEffectTypes::throwItem);
                m_PickupItem->Throw(Vector2f{m_IsLookingToLeft ? -1000.0f : 1000.0f, -300.0f});
            }
            
            m_PickupItem = nullptr;
        }
    }
}

void PlayerObject::CheckBomb()
{
    if(m_InputManager->PressedBombThisFrame())
    {
        if(m_BombLeftAmount <= 0) return;
        --m_BombLeftAmount;
        Bomb* bomb = m_WorldManager->GetEntityManager()->CreateBomb();
        const Vector2f spawnLocation = GetCenter() + Vector2f{m_IsLookingToLeft ? -20.0f : 20.0f, -10};
        
        if(m_IsCrouching)
        {
            bomb->Throw(spawnLocation, Vector2f{m_IsLookingToLeft ? -300.0f : 300.0f, -10.0f});
        }
        else
        {
            bomb->Throw(spawnLocation, Vector2f{m_IsLookingToLeft ? -1000.0f : 1000.0f, -300.0f});
        }
    }
}
void PlayerObject::CheckCrouching(const Vector2f& moveInput)
{
    m_IsCrouching = false;
    if(m_PlayerState == PlayerState::normal)
    {
        if(m_IsOnGround && !m_IsOnLadder)
        {
            if(moveInput.y > 0.1)
            {
                m_IsCrouching = true;
            }
        }
    }
}
void PlayerObject::PlayerInteract()
{
    if(m_InputManager->PressedInteractThisFrame())
    {
        if(m_CanLeaveCave)
        {
            m_PlayerState = PlayerState::enteringLeaving;
        }
    }
}
void PlayerObject::HealPlayer()
{
    ++m_Health;
}

void PlayerObject::YouGotHit(const int damage, const Vector2f& force)
{
    if(m_InvisibilityFrames) return;
    m_InvisibilityFrames = true;
    m_InvisibilityTimer = 0.5f;

    m_SoundManager->PlaySoundEffect(SoundEffectTypes::hit);
    
    if(force.SquaredLength() > 100*100)
    {
        m_PlayerState = PlayerState::ragdoll;
        m_RagDollTimer = 0.5f;
        m_IsWiping = false;
        m_IsOnLadder = false;
        m_IsCrouching = false;
        ChangeAnimationState(PlayerAnimationState::ragdoll);
        m_PhysicsCollider.SetBounciness(0.3f);
    }
    
    m_Health -= damage;
    m_PhysicsCollider.ApplyForce(force*2);
    if(m_Health <= 0)
    {
        m_PlayerState = PlayerState::dead;
    }
}
void PlayerObject::HandleWallHanging(const float elapsedTimes)
{
    if(m_IsTouchingWall && !(m_InputManager->GetMoveInput().y > 0))
    {
        if(m_IsJumping == false)
        {
            const float characterTopHeight = GetRect().top ;
            const float characterNewTopHeight = GetRect().top + m_PhysicsCollider.GetVelocity().y * elapsedTimes;

            const int characterTileY = int(characterTopHeight / Game::TILE_SIZE);
            const int characterNewTileY = int(characterNewTopHeight / Game::TILE_SIZE);
                
            if(characterTileY != characterNewTileY)
            {
                const Vector2i currentTileIndex{int(GetPosition().x / Game::TILE_SIZE), characterTileY};
                const Vector2i hangingDirection = m_IsTouchingLeftWall ? Vector2i{-1, 0} : Vector2i{1, 0};
                    
                Cave* cave = m_WorldManager->GetCave();
                if (cave->GetTile(currentTileIndex.x + hangingDirection.x, currentTileIndex.y).GetTileType() == TileTypes::air &&
                    cave->GetTile(currentTileIndex.x + hangingDirection.x, currentTileIndex.y + 1).GetTileType() == TileTypes::ground
                )
                {
                    m_PlayerState = PlayerState::hanging;
                    m_IsWiping = false;
                    m_PhysicsCollider.SetVelocity(0, 0);
                    m_PhysicsCollider.SetRect(Rectf{GetRect().left, static_cast<float>(currentTileIndex.y + 1) * Game::TILE_SIZE, GetRect().width, GetRect().height});
                }
            }
        }
    }
}
void PlayerObject::Respawn(const Vector2f& spawnLocation)
{
    if(m_PlayerState == PlayerState::dead)
    {
        m_BombLeftAmount = 4;
    }
    
    m_PhysicsCollider.SetCenter(spawnLocation);
    m_Health = 4;
    m_AnimationFrame = 0;
    m_AnimationTimer = 0;
    
    m_IsOnGround = false;
    m_IsJumping = false;
    m_IsOnLadder = false;
    m_IsCrouching = false;
    m_PhysicsCollider.SetBounciness(0);
    
    m_PickupItem = nullptr;
    m_InvisibilityFrames = false;
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
bool PlayerObject::CanPlayerLeave() const
{
    return m_CanLeaveCave;
}
int PlayerObject::GetBombsAmount() const
{
    return m_BombLeftAmount;
}
int PlayerObject::GetRopeAmount() const
{
    return 0;
}
