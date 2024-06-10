#include "pch.h"
#include "UIManager.h"

#include "Texture.h"
#include "WorldManager.h"

UiManager::UiManager(WorldManager* worldManager):
	m_PlayerHudTexture(new Texture{"ANYLEVEL/playerhud.png"}),
	m_WorldManager(worldManager)
{
}
UiManager::~UiManager()
{
	delete m_PlayerHudTexture;
	delete m_HealthText;
	delete m_BombText;
	delete m_BombOutLineText;
	delete m_RopeOutLineText;
	delete m_RopeText;
}


void UiManager::Draw()
{
	m_PlayerHudTexture->Draw(Rectf{50, 25, 512*0.6f, 128*0.6f}, Rectf{0,0, 512, 128});
	if(m_PrevPlayerHealth != m_WorldManager->GetPlayer()->GetHealth())
	{
		m_PrevPlayerHealth = m_WorldManager->GetPlayer()->GetHealth();

		delete m_HealthText;
		m_HealthText = new Texture{std::to_string(m_PrevPlayerHealth), "Life-Is-Okay.ttf", 40, {1,0.9f,0.9f}};
	}

	if(m_PrevPlayerBombs != m_WorldManager->GetPlayer()->GetBombsAmount())
	{
		m_PrevPlayerBombs = m_WorldManager->GetPlayer()->GetBombsAmount();

		delete m_BombText;
		delete m_BombOutLineText;
		m_BombText = new Texture{std::to_string(m_PrevPlayerBombs), "Life-Is-Okay.ttf", 40, {1,1,1}};
		m_BombOutLineText = new Texture{std::to_string(m_PrevPlayerBombs), "Life-Is-Okay.ttf", 45, {0,0,0}};
	}
	
	if(m_PrevPlayerRopes != m_WorldManager->GetPlayer()->GetRopeAmount())
	{
		m_PrevPlayerRopes = m_WorldManager->GetPlayer()->GetRopeAmount();

		delete m_RopeText;
		delete m_RopeOutLineText;
		m_RopeText = new Texture{std::to_string(m_PrevPlayerRopes), "Life-Is-Okay.ttf", 40, {1,1,1}};
		m_RopeOutLineText = new Texture{std::to_string(m_PrevPlayerRopes), "Life-Is-Okay.ttf", 45, {0,0,0}};
	}

	m_HealthText->Draw(Vector2f{78, 40});
	m_BombOutLineText->Draw(Vector2f{150, 35});
	m_BombText->Draw(Vector2f{150, 35});
	m_RopeOutLineText->Draw(Vector2f{240, 35});
	m_RopeText->Draw(Vector2f{240, 35});
}
