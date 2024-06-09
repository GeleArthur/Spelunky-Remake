#pragma once
#include "Entity.h"
#include "EntityPickupRectCollider.h"

class PlayerObject;
class Cave;
class SpriteSheetManager;
class Damsel final : public EntityPickupRectCollider
{
public:
	explicit Damsel(const Vector2f& position, bool facingLeft, WorldManager* worldManager);
	virtual EntityType GetEntityType() const override;
	virtual void Draw() const override;
	virtual void Throw(const Vector2f& force) override;
	virtual void Update(float elapsedTime) override;
	virtual bool TryToPickUp(Entity* pickedUpBy) override;
	virtual void YouGotHit(int damage, const Vector2f& force) override;

private:
	bool m_IsWalkingAround{false};
	bool m_Ragdolling{false};
	float m_RagDollTimer{};

	bool m_MovingLeft{false};
	float m_AnimationTimer{0};
	
	SpriteSheetManager* m_SpriteSheetManager;
	Cave* m_Cave;
	PlayerObject* m_Player;
};
