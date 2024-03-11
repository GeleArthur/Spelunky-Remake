#pragma once
class Texture;

class SpriteSheetManager
{
public:
	SpriteSheetManager();
	~SpriteSheetManager();

	static SpriteSheetManager* GetSingleton();
	void DrawTile(Vector2f position, int x, int y) const;

	Texture* m_CurrentPlayerTexture;
	Texture* m_LevelTexture;
	Texture* m_BackGroundImage;

private:
	static SpriteSheetManager* m_pSpriteSheetManager;



};

