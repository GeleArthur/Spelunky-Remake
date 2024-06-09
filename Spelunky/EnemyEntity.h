#pragma once
#include "Entity.h"

class EnemyEntity : public Entity
{
public:
	EnemyEntity(const Rectf& collider, const int health, const float mass, const float bounciness, WorldManager* worldManager);

	void CheckToHurtPlayer();

protected:
	WorldManager* m_WorldManager;
};
