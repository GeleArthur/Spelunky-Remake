#include "pch.h"
#include "Rock.h"

#include "SpriteSheetManager.h"
#include "Texture.h"


Rock::Rock(const Vector2f& position, const SpriteSheetManager* spriteSheetManager ,const std::vector<std::vector<Tile>>& tiles):
    PhysicsObject(position, tiles),
    m_SpriteSheetManager(spriteSheetManager)
{
}

void Rock::Update(const float elapsedTime)
{
    UpdatePhysics(elapsedTime);
}

void Rock::Draw()
{
    m_SpriteSheetManager->GetItemsTexture()->Draw(m_Position, Rectf{1360, 0, 80,80});
}
