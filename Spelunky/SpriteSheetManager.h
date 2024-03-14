#pragma once
enum class TileTypes;
class Texture;

class SpriteSheetManager
{
public:
	SpriteSheetManager();
	~SpriteSheetManager();

	static SpriteSheetManager* GetSingleton();
	Texture* GetLevelTexture() const;
	Texture* GetBackGroundTexture() const;

private:
	static SpriteSheetManager* m_pSpriteSheetManager;

	Texture* m_CurrentPlayerTexture;
	Texture* m_LevelTexture;
	Texture* m_BackGroundImage;
};

