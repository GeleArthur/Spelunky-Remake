#pragma once
// SMART POINTERS WHEN AAAAAAARGGGGGG

class WorldManager;
enum class TileTypes;
class Texture;

class SpriteSheetManager final
{
public:
	SpriteSheetManager(WorldManager* worldManager);
	~SpriteSheetManager();
	SpriteSheetManager(const SpriteSheetManager& other) = delete; // If we do this something went wrong 
	SpriteSheetManager& operator=(const SpriteSheetManager& other) = delete;

	Texture* GetLevelTexture() const;
	Texture* GetBackGroundTexture() const;
	Texture* GetDoorsTexture() const;
	Texture* GetCurrentPlayerTexture() const;
	Texture* GetItemsTexture() const;

private:
	Texture* m_CurrentPlayerTexture;
	Texture* m_LevelTexture;
	Texture* m_BackGroundTexture;
	Texture* m_ExitDoorsTexture;
	Texture* m_ItemsTexture;
};

