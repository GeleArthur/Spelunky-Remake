#include "pch.h"
#include "Rock.h"

#include "CircleCollider.h"
#include "RectCollider.h"
#include "SpriteSheetManager.h"
#include "Texture.h"


Rock::Rock(const Vector2f& position, const SpriteSheetManager* spriteSheetManager ,const std::vector<std::vector<Tile>>* tiles):
    PhysicsObject(new RectCollider{Rectf{position.x,position.y,30,30}}, tiles),
    m_SpriteSheetManager(spriteSheetManager)
{
}

Rock::~Rock() = default;

void Rock::Update(const float elapsedTime)
{
    UpdatePhysics(elapsedTime);
}

void Rock::Draw() const
{
    GetCollider()->DebugDraw();
    m_SpriteSheetManager->GetItemsTexture()->Draw(
        GetCollider()->GetOrigin() - Vector2f{40, 40},
        Rectf{1360, 0, 80,80}
    );
}
