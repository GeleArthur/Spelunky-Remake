#include "pch.h"
#include "EnemyEntity.h"
#include "WorldManager.h"

EnemyEntity::EnemyEntity(const Rectf& collider, const int health, const float mass, const float bounciness, WorldManager* worldManager):
	Entity(collider, health, mass, bounciness, worldManager), m_WorldManager(worldManager)
{
}

void EnemyEntity::CheckToHurtPlayer()
{
	const std::vector<std::pair<RayVsRectInfo, Entity*>>& entities = m_PhysicsCollider.GetEntitiesWeHit();

	for (const std::pair<RayVsRectInfo, Entity*>& entity : entities)
	{
		if (entity.second->GetEntityType() == EntityType::player)
		{
			const Vector2f distance = m_WorldManager->GetPlayer()->GetPosition() - GetCenter();
			entity.second->YouGotHit(1, Vector2f{ distance.Normalized() * 400 });
		}
	}

}
