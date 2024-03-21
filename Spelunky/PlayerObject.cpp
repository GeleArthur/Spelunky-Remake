#include "pch.h"
#include "PlayerObject.h"

#include <vector>

#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Tile.h"

PlayerObject::PlayerObject(const Vector2f startPosition, SpriteSheetManager* spriteSheetManager, const std::vector<std::vector<Tile>>& tiles):
    PhysicsObject(startPosition, m_WorldTiles),
    m_SpriteSheetManager(spriteSheetManager)
{
}

void PlayerObject::Draw() const
{
    // TODO: animation system
    m_SpriteSheetManager->GetCurrentPlayerTexture()->Draw(m_Position - Vector2f{40,40}, Rectf{0,0,80,80});
}

void PlayerObject::Update(const float elapsedTimes)
{
    UpdatePhysics(elapsedTimes);
}
