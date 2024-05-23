#include "pch.h"
#include "Bat.h"

#include "SpriteSheetManager.h"
#include "Texture.h"
#include "utils.h"
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
	if(m_IsAttacking)
	{
		
	}
	else
	{
		glPushMatrix();
		glTranslatef(GetCenter().x, GetCenter().y, 0);
		m_SpriteSheetManager->GetMonsterTexture3()->Draw(
			Vector2f{-40,-40},
			Rectf{static_cast<float>(m_AnimationFrame)*80.0f,5*80.0f,80.0f,80.0f});
		glPopMatrix();
	}
	
}
void Bat::Update(float elapsedTime)
{
	if(IsDead()) return;

	m_AnimationTimer += elapsedTime;

	if(m_IsAttacking)
	{
		
	}
	else
	{
		// if(m_IsAnimatingSleep)
		// {
		// 	
		// 	if(m_AnimationTimer > 0.1)
		// 	{
		// 		m_AnimationFrame = m_AnimationFrame+1;
		// 		m_AnimationTimer = 0;
		// 		if(m_AnimationFrame >= 7)
		// 		{
		// 			m_AnimationFrame = 0;
		// 			m_AnimationTimer = utils::Random(0.0f, 2.0f);
		// 			m_IsAnimatingSleep = false;
		// 		}
		// 	}
		// }
		// else
		// {
		// 	if(m_AnimationTimer > 5)
		// 	{
		// 		m_IsAnimatingSleep = true;
		// 		m_AnimationTimer = 0;
		// 		m_AnimationFrame = 0;
		// 	}
		// }

	}
	
	
	UpdatePhysics(elapsedTime);
}
