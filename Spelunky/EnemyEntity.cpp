#include "pch.h"
#include "EnemyEntity.h"

#include "WorldManager.h"
void EnemyEntity::CheckToHurtPlayer()
{
	const std::vector<std::pair<RayVsRectInfo, Entity*>>& entities = m_PhysicsCollider.GetEntitiesWeHit();

	for (const std::pair<RayVsRectInfo, Entity*>& entity : entities)
	{
		if(entity.second->GetEntityType() == EntityType::player)
		{
			const Vector2f distance = m_WorldManager->GetPlayer()->GetPosition() - GetCenter();
			entity.second->YouGotHit(1, Vector2f{distance.Normalized() * 400});
		}
	}

}
