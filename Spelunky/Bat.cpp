#include "pch.h"
#include "Bat.h"

#include "Cave.h"
#include "GizmosDrawer.h"
#include "GlobalValues.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Tile.h"
#include "utils.h"
Bat::Bat(const Tile* attachedTile, WorldManager* worldManager):
	EntityRectCollider(Rectf{attachedTile->GetCenter().x - 25, attachedTile->GetCenter().y - 25 + spelucky_settings::g_TileSize, 50, 50 }, 1, 1, 0, worldManager),
	m_SpriteSheetManager(worldManager->GetSpriteSheet()),
	m_WorldManager(worldManager),
	m_AttachedTile(attachedTile)
{
}

EntityType Bat::GetEntityType() const
{
	return EntityType::bat;
}
void Bat::Draw() const
{
	if(IsDead()) return;

	
	glPushMatrix();
	if(m_IsAttacking)
	{
		glTranslatef(GetCenter().x, GetCenter().y, 0);
		if(GetVelocity().x < 0)
			glScalef(-1,1,1);
		
		m_SpriteSheetManager->GetMonsterTexture3()->Draw(
			Vector2f{-40,-40},
			Rectf{static_cast<float>(m_AnimationFrame)*80.0f, 6*80.0f, 80.0f, 80.0f});
	}
	else
	{
		glTranslatef(GetCenter().x, GetCenter().y, 0);
		m_SpriteSheetManager->GetMonsterTexture3()->Draw(
			Vector2f{-40,-40},
			Rectf{0,5*80.0f,80.0f,80.0f});
	}
	glPopMatrix();
}
void Bat::Update(const float elapsedTime)
{
	if(IsDead()) return;
	
	
	if(m_IsAttacking)
	{
		m_AnimationTimer += elapsedTime;
		
		if(m_AnimationTimer > 0.05f)
		{
			m_AnimationTimer = 0;
			m_AnimationFrame = (++m_AnimationFrame) % 7;
		}

		SetVelocity((m_WorldManager->GetPlayer()->GetPosition() - GetCenter()).Normalized() * 64);
	}
	else
	{
		if(m_AttachedTile != nullptr)
		{
			if(m_AttachedTile->GetTileType() == TileTypes::air)
			{
				m_IsAttacking = true;
				m_AttachedTile = nullptr;
			}
		}

		Vector2f distance = m_WorldManager->GetPlayer()->GetPosition() - GetCenter();
		
		if(distance.SquaredLength() < 10*spelucky_settings::g_TileSize*10*spelucky_settings::g_TileSize)
		{
			const std::vector<std::vector<Tile*>>& tiles = m_WorldManager->GetCave()->GetTiles();

			bool CanSeePlayer{true};
			
			for (int x{}; x < static_cast<int>(tiles.size()); ++x)
			{
				for (int y{}; y < static_cast<int>(tiles[x].size()); ++y)
				{
					const Tile* currentTile = tiles[x][y];
					if(currentTile->GetTileType() == TileTypes::air) continue;

					RayVsRectInfo rayResult;
					if (RayCastCollision(GetCenter(), distance, currentTile->GetRect(), rayResult))
					{
						CanSeePlayer = false;
						break;
					}
				}
				if(CanSeePlayer == false) break;
			}

			if(CanSeePlayer)
			{
				m_IsAttacking = true;
			}
		}
	}
	
	UpdatePhysics(elapsedTime);
}
