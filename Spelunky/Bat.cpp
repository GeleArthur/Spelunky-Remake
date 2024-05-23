#include "pch.h"
#include "Bat.h"

#include "GizmosDrawer.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Tile.h"
#include "utils.h"
Bat::Bat(const Tile* attachedTile, WorldManager* worldManager):
	EntityRectCollider(Rectf{attachedTile->GetCenter().x - 25, attachedTile->GetCenter().y - 25, 50, 50 }, 1, 1, 0, worldManager),
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
	if(IsDead()) return;

	if(m_IsAttacking)
	{
		
	}
	else
	{
		glPushMatrix();
		glTranslatef(GetCenter().x, GetCenter().y, 0);
		m_SpriteSheetManager->GetMonsterTexture3()->Draw(
			Vector2f{-40,-40},
			Rectf{0,5*80.0f,80.0f,80.0f});
		glPopMatrix();
	}
	
}
void Bat::Update(const float elapsedTime)
{
	if(IsDead()) return;
	m_AnimationTimer += elapsedTime;

	if(m_IsAttacking)
	{
		
	}
	
	UpdatePhysics(elapsedTime);
}
