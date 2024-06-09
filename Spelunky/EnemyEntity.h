#pragma once
#include "Entity.h"

class EnemyEntity : public Entity
{
public:
	EnemyEntity(const Rectf& collider, int health, float mass, float bounciness, bool invisible, WorldManager* worldManager);

	void CheckToHurtPlayer();

protected:
	WorldManager* m_WorldManager;
};
