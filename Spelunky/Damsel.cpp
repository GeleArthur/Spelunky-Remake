#include "pch.h"
#include "Damsel.h"

#include "Cave.h"
#include "Game.h"
#include "GizmosDrawer.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "TileTypes.h"
#include "Vector2i.h"
#include "WorldManager.h"

Damsel::Damsel(const Vector2f& position, const bool facingLeft, WorldManager* worldManager):
	EntityPickupRectCollider(Rectf{ position.x, position.y, 55, 49 }, 4, 1, 0, false, worldManager),
	m_MovingLeft(facingLeft),
	m_Player(worldManager->GetPlayer()),
	m_SpriteSheetManager(worldManager->GetSpriteSheet()),
	m_Cave(worldManager->GetCave())
{
}

EntityType Damsel::GetEntityType() const
{
	return EntityType::damsel;
}

void Damsel::Draw() const
{
	if(IsDead()) return;
	
	glPushMatrix();
	glTranslatef(GetCenter().x, GetCenter().y, 0);
	
	if(!m_MovingLeft)
		glScalef(-1,1,1);

	if(!m_IsWalkingAround)
	{
		m_SpriteSheetManager->GetMonsterBigTexture3()->Draw(
			Vector2f{-41,-47},
			Rectf{2*80, 0, 80.0f, 80.0f});
	}
	else if(m_Ragdolling)
	{
		if(IsPickedUp())
		{
			m_SpriteSheetManager->GetMonsterBigTexture3()->Draw(
				Vector2f{-41,-47},
				Rectf{5*80, 80, 80.0f, 80.0f});
		}
		
		else if(m_PhysicsCollider.GetVelocity().SquaredLength() < 100)
		{
			m_SpriteSheetManager->GetMonsterBigTexture3()->Draw(
				Vector2f{-41,-47},
				Rectf{11*80, 0, 80.0f, 80.0f});
		}
		else
		{
			m_SpriteSheetManager->GetMonsterBigTexture3()->Draw(
				Vector2f{-41,-47},
				Rectf{2*80, 80, 80.0f, 80.0f});
		}
	}
	else
	{
		m_SpriteSheetManager->GetMonsterBigTexture3()->Draw(
			Vector2f{-41,-47},
			Rectf{80*3 + (int(m_AnimationTimer*1/0.1f)%8)*80.0f, 0, 80.0f, 80.0f});
	}
	

	glPopMatrix();
}

void Damsel::Update(const float elapsedTime)
{
	if(IsDead()) return;
	m_AnimationTimer += elapsedTime;
	
	if(m_IsWalkingAround && !IsPickedUp())
	{
		if(m_Ragdolling)
		{
			if(IsOnGround())
			{
				const Vector2f& velocity = m_PhysicsCollider.GetVelocity();
				Vector2f newVelocity{
					std::max(std::abs(velocity.x) * 0.3f - 0.2f, 0.0f) * (velocity.x >= 0 ? 1.0f : -1.0f),
					std::max(std::abs(velocity.y) * 0.3f - 0.2f, 0.0f) * (velocity.y >= 0 ? 1.0f : -1.0f)
				};
        
				m_PhysicsCollider.SetVelocity(newVelocity);
			}
			
			if(m_PhysicsCollider.GetVelocity().SquaredLength() <= 10)
			{
				m_RagDollTimer -= elapsedTime;
				if(m_RagDollTimer < 0)
				{
					m_PhysicsCollider.SetBounciness(0);
					m_Ragdolling = false;
				}
			}
		}
		else
		{
			m_PhysicsCollider.SetVelocity(m_MovingLeft ? Vector2f{100 , m_PhysicsCollider.GetVelocity().y} : Vector2f{-100, m_PhysicsCollider.GetVelocity().y});
			
			const Vector2i nextTile = Vector2i((GetCenter() + (m_MovingLeft ? Vector2f{-25, 0}: Vector2f{25, 0}))  / Game::TILE_SIZE) + Vector2i{m_MovingLeft ? 1 : -1, 0};
			const TileTypes inFrontOfMe = m_Cave->GetTile(nextTile).GetTileType();
		
			if(inFrontOfMe == TileTypes::ground || inFrontOfMe == TileTypes::border)
			{
				m_MovingLeft = !m_MovingLeft;
			}
		}

	}
	
	EntityPickupRectCollider::Update(elapsedTime);

	const std::vector<std::pair<const Tile*, RayVsRectInfo>>& tiles = m_PhysicsCollider.GetTilesWeHit();
	for (const std::pair<const Tile*, RayVsRectInfo>& tile : tiles)
	{
		switch(tile.first->GetTileType())
		{
		case TileTypes::exit:
			m_Health = 0;
			m_Player->HealPlayer();
			break;
		case TileTypes::air:
		case TileTypes::ground:
		case TileTypes::border:
		case TileTypes::ladderTop:
		case TileTypes::ladder:
		case TileTypes::spikes:
		case TileTypes::pushBlock:
		case TileTypes::entrance:
		case TileTypes::unknown:
			break;
		}
	}
}
bool Damsel::TryToPickUp(Entity* pickedUpBy)
{
	const bool isPickup = EntityPickupRectCollider::TryToPickUp(pickedUpBy);

	if(isPickup)
	{
		m_Ragdolling = true;
		m_PhysicsCollider.SetBounciness(0.3f);
		m_IsWalkingAround = true;
	}
	return isPickup;
}
void Damsel::YouGotHit(const int damage, const Vector2f& force)
{
	m_PhysicsCollider.SetBounciness(0.3f);
	m_Ragdolling = true;
	m_IsWalkingAround = true;
	m_RagDollTimer = 2;
	EntityPickupRectCollider::YouGotHit(damage, force);
}


void Damsel::Throw(const Vector2f& force)
{
	m_MovingLeft = force.x > 0;
	m_Ragdolling = true;
	m_RagDollTimer = 2;
	
	EntityPickupRectCollider::Throw(force);
}
