#include "pch.h"
#include "PlayerObject.h"

#include <vector>

#include "CircleCollider.h"
#include "RectCollider.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Tile.h"

PlayerObject::PlayerObject(SpriteSheetManager* spriteSheetManager, const std::vector<std::vector<Tile>>* tiles):
     PhysicsObject(Vector2f{64,0}, new RectCollider{Rectf{0,0,64,64}, this}, tiles),
    m_SpriteSheetManager(spriteSheetManager)
{
}

void PlayerObject::Draw() const
{
    // TODO: animation system
    m_SpriteSheetManager->GetCurrentPlayerTexture()->Draw(GetCollider()->GetCenterPosition() - Vector2f{40,40}, Rectf{0,0,80,80});
    GetCollider()->DebugDraw();
}

void PlayerObject::Update(const float elapsedTimes)
{
    UpdatePhysics(elapsedTimes);
}
