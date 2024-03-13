#pragma once
enum class TileTypes;
class Texture;

class SpriteSheetManager
{
public:
	SpriteSheetManager();
	~SpriteSheetManager();

	static SpriteSheetManager* GetSingleton();
	void DrawTile(const Vector2f position, const TileTypes type, int variant) const;

	Texture* m_CurrentPlayerTexture;
	Texture* m_LevelTexture;
	Texture* m_BackGroundImage;

private:
	static SpriteSheetManager* m_pSpriteSheetManager;



};

