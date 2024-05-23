#include "pch.h"
#include "Bat.h"
Bat::Bat(const Vector2f& position, WorldManager* worldManager):
	EntityRectCollider(Rectf{ position.x, position.y, 20, 20 }, 1, 1, 0, worldManager),
	m_SpriteSheetManager(worldManager->GetSpriteSheet())
{
}

EntityType Bat::GetEntityType() const
{
	return EntityType::bat;
}
void Bat::Draw() const
{
	if(IsDead()) return;

	
}
void Bat::Update(float elapsedTime)
{
	if(IsDead()) return;

	
	
	UpdatePhysics(elapsedTime);
}
