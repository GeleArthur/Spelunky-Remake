#pragma once
class Texture;

class SpriteSheetManager
{
public:
	SpriteSheetManager();
	~SpriteSheetManager();

	static SpriteSheetManager* GetSingleton();
	void DrawTile(Vector2f position, int x, int y) const;
	Texture* m_LevelTexture;

private:
	Texture* m_CurrentPlayerTexture;
	static SpriteSheetManager* m_pSpriteSheetManager;
};

