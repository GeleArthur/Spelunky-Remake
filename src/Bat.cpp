
#include "Bat.h"

#include "Cave.h"
#include "Game.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Tile.h"


Bat::Bat(const Tile* attachedTile, WorldManager* worldManager):
	EnemyEntity(Rectf{ attachedTile->GetCenter().x - 25, attachedTile->GetCenter().y - 25 + Game::TILE_SIZE, 50, 50 }, 1, 1, 0, false, worldManager),
	m_SpriteSheetManager(worldManager->GetSpriteSheet()),
	m_AttachedTile(attachedTile)
{
}

EntityType Bat::GetEntityType() const
{
	return EntityType::bat;
}
void Bat::Draw() const
{
	if (IsDead()) return;

	glPushMatrix();
	glTranslatef(GetCenter().x, GetCenter().y, 0);

	if (m_IsAttacking)
	{
		if (m_PhysicsCollider.GetVelocity().x < 0)
			glScalef(-1, 1, 1);

		m_SpriteSheetManager->GetMonsterTexture3()->Draw(
			Vector2f{ -40, -40 },
			Rectf{ static_cast<float>(m_AnimationFrame) * 80.0f, 6 * 80.0f, 80.0f, 80.0f });
	}
	else
	{
		m_SpriteSheetManager->GetMonsterTexture3()->Draw(
			Vector2f{ -40, -40 },
			Rectf{ 0, 5 * 80.0f, 80.0f, 80.0f });
	}
	glPopMatrix();
}

void Bat::Update(const float elapsedTime)
{
	if (IsDead()) return;

	if (m_IsAttacking)
	{
		m_AnimationTimer += elapsedTime;

		if (m_AnimationTimer > 0.05f)
		{
			m_AnimationTimer = 0;
			m_AnimationFrame = (++m_AnimationFrame) % 7;
		}

		m_PhysicsCollider.SetVelocity((m_WorldManager->GetPlayer()->GetPosition() - GetCenter()).Normalized() * 64);
	}
	else
	{
		if (m_AttachedTile != nullptr)
		{
			if (m_AttachedTile->GetTileType() == TileTypes::air)
			{
				m_IsAttacking = true;
				m_AttachedTile = nullptr;
			}
		}

		const Vector2f distance = m_WorldManager->GetPlayer()->GetPosition() - GetCenter();

		if (distance.SquaredLength() < 5 * Game::TILE_SIZE * 5 * Game::TILE_SIZE)
		{
			const std::vector<std::vector<Tile*>>& tiles = m_WorldManager->GetCave()->GetTiles();

			bool canSeePlayer{ true };

			for (int x{}; x < static_cast<int>(tiles.size()); ++x)
			{
				for (int y{}; y < static_cast<int>(tiles[x].size()); ++y)
				{
					const Tile* currentTile = tiles[x][y];
					if (currentTile->GetTileType() == TileTypes::air) continue;

					RayVsRectInfo rayResult;
					if (RectPhysicsCollider::RayCastCollision(GetCenter(), distance, currentTile->GetRect(), rayResult))
					{
						canSeePlayer = false;
						break;
					}
				}
				if (canSeePlayer == false) break;
			}

			if (canSeePlayer)
			{
				m_IsAttacking = true;
			}
		}
	}


	m_PhysicsCollider.UpdatePhysics(elapsedTime);
	const std::vector<std::pair<const Tile*, RayVsRectInfo>>& tiles = m_PhysicsCollider.GetTilesWeHit();
	for (const std::pair<const Tile*, RayVsRectInfo> tile : tiles)
	{
		if (tile.first->GetTileType() == TileTypes::spikes)
		{
			if (m_PhysicsCollider.GetVelocity().y > 0)
			{
				m_Health -= 100;
			}
		}
	}

	CheckToHurtPlayer();
}
