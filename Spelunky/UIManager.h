#pragma once

class Texture;
class WorldManager;

class UiManager final
{
public:
	explicit UiManager(WorldManager* worldManager);
	~UiManager();
	UiManager( const UiManager& other ) = delete;
	UiManager& operator=( const UiManager& rhs ) = delete;
	UiManager(UiManager&& other) = delete;
	UiManager& operator=(UiManager&& other) = delete;
	
	void Draw();

private:
	int m_PrevPlayerHealth{-1};
	int m_PrevPlayerBombs{-1};
	int m_PrevPlayerRopes{-1};
	
	Texture* m_PlayerHudTexture;
	Texture* m_HealthText{};
	Texture* m_BombText{};
	Texture* m_BombOutLineText{};
	Texture* m_RopeText{};
	Texture* m_RopeOutLineText{};
	WorldManager* m_WorldManager;
};
