#pragma once
#include "EntityRectCollider.h"
#include "WorldManager.h"

class SpriteSheetManager;
class Bat final : public EntityRectCollider
{
public:
	Bat(const Vector2f& position, WorldManager* worldManager);
	EntityType GetEntityType() const override;
	void Draw() const override;
	virtual void Update(float elapsedTime) override;

private:
	SpriteSheetManager* m_SpriteSheetManager;
	bool m_IsAttacking{};
	bool m_IsAnimatingSleep{};
	float m_AnimationTimer{};
	int m_AnimationFrame{};

	Tile* m_AttachedTile{};

};
