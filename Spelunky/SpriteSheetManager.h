#pragma once
// SMART POINTERS WHEN AAAAAAARGGGGGG

class WorldManager;
enum class TileTypes;
class Texture;

class SpriteSheetManager final
{
public:
	explicit SpriteSheetManager(WorldManager* worldManager);
	~SpriteSheetManager();
	SpriteSheetManager(const SpriteSheetManager& other) = delete;
	SpriteSheetManager& operator=(const SpriteSheetManager& other) = delete;
	SpriteSheetManager(SpriteSheetManager&& other) = delete;
	SpriteSheetManager& operator=(SpriteSheetManager&& other) = delete;

	const Texture* GetLevelTexture() const;
	const Texture* GetBackGroundTexture() const;
	const Texture* GetDoorsTexture() const;
	const Texture* GetCurrentPlayerTexture() const;
	const Texture* GetItemsTexture() const;
	const Texture* GetMonsterTexture() const; 
	const Texture* GetMonsterTexture3() const; 

private:
	Texture* m_CurrentPlayerTexture;
	Texture* m_LevelTexture;
	Texture* m_BackGroundTexture;
	Texture* m_ExitDoorsTexture;
	Texture* m_ItemsTexture;
	Texture* m_MonsterTexture;
	Texture* m_MonsterTexture3;
};

