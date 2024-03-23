#include "pch.h"
#include "Rock.h"

#include "CircleCollider.h"
#include "SpriteSheetManager.h"
#include "Texture.h"


Rock::Rock(const Vector2f& position, const SpriteSheetManager* spriteSheetManager ,const std::vector<std::vector<Tile>>* tiles):
    PhysicsObject(position, new CircleCollider{Vector2f{}, 30}, tiles),
    m_SpriteSheetManager(spriteSheetManager)
{
}

void Rock::Update(const float elapsedTime)
{
    UpdatePhysics(elapsedTime);
}

void Rock::Draw()
{
    GetCollider()->DebugDraw();
    m_SpriteSheetManager->GetItemsTexture()->Draw(GetCollider()->GetCenterPosition(), Rectf{1360, 0, 80,80});
}
