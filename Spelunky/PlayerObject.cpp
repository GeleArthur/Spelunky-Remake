#include "pch.h"
#include "PlayerObject.h"

#include <vector>

#include "CircleCollider.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Tile.h"

PlayerObject::PlayerObject(SpriteSheetManager* spriteSheetManager, const std::vector<std::vector<Tile>>* tiles):
    PhysicsObject(Vector2f{0,0}, new CircleCollider{Vector2f{}, 50, this}, tiles),
    m_SpriteSheetManager(spriteSheetManager)
{
}

void PlayerObject::Draw() const
{
    // TODO: animation system
    m_SpriteSheetManager->GetCurrentPlayerTexture()->Draw(GetCollider()->GetCenterPosition() - Vector2f{40,40}, Rectf{0,0,80,80});
}

void PlayerObject::Update(const float elapsedTimes)
{
    UpdatePhysics(elapsedTimes);
}
