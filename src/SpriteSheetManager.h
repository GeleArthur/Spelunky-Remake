#pragma once
#include <SDL_ttf.h>
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
	const Texture* GetMonsterBigTexture3() const; 
	const Texture* GetHudElementTexture() const; 
	const Texture* GetSpaceText() const; 

private:
	Texture* m_CurrentPlayerTexture;
	Texture* m_LevelTexture;
	Texture* m_BackGroundTexture;
	Texture* m_ExitDoorsTexture;
	Texture* m_ItemsTexture;
	Texture* m_MonsterTexture;
	Texture* m_MonsterTexture3;
	Texture* m_MonsterBigTexture3;
	Texture* m_HudElementTexture;
	Texture* m_SpaceText;
	TTF_Font* m_HudFont;
};

