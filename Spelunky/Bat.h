#pragma once
#include "Entity.h"
#include "WorldManager.h"

class SpriteSheetManager;
class Bat final : public Entity
{
public:
	Bat(const Tile* attachedTile, WorldManager* worldManager);
	virtual EntityType GetEntityType() const override;
	virtual void Draw() const override;
	virtual void Update(float elapsedTime) override;
	
private:
	SpriteSheetManager* m_SpriteSheetManager;
	WorldManager* m_WorldManager;
	bool m_IsAttacking{false};
	
	float m_AnimationTimer{};
	int m_AnimationFrame{};

	const Tile* m_AttachedTile;
};
