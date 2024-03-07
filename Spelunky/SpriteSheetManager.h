#pragma once
class Texture;

class SpriteSheetManager
{
public:
	SpriteSheetManager();
	~SpriteSheetManager();

private:
	Texture* m_CurruntPlayerTexture;
	Texture* m_LevelTexture;
};

