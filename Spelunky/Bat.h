#pragma once
#include "EntityRectCollider.h"
#include "WorldManager.h"

class SpriteSheetManager;
class Bat final : EntityRectCollider
{
public:
	Bat(const Vector2f& position, WorldManager* worldManager);
	EntityType GetEntityType() const override;
	void Draw() const override;
	virtual void Update(float elapsedTime) override;

private:
	SpriteSheetManager* m_SpriteSheetManager;

};
