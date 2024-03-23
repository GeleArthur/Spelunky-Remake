#include "pch.h"
#include "PlayerObject.h"

#include <vector>

#include "CircleCollider.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Tile.h"

PlayerObject::PlayerObject(Collider* collider, SpriteSheetManager* spriteSheetManager, const std::vector<std::vector<Tile>>* tiles):
    PhysicsObject(collider, tiles),
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
