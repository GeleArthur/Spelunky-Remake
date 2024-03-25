﻿#include "pch.h"
#include "Rock.h"

#include "CircleCollider.h"
#include "SpriteSheetManager.h"
#include "Texture.h"


Rock::Rock(const Vector2f& position, const SpriteSheetManager* spriteSheetManager ,const std::vector<std::vector<Tile>>* tiles):
    PhysicsObject(position, new CircleCollider{Vector2f{}, 30, this}, tiles),
    m_SpriteSheetManager(spriteSheetManager)
{
}

void Rock::Update(const float elapsedTime)
{
    UpdatePhysics(elapsedTime);
}

void Rock::Draw() const
{
    GetCollider()->DebugDraw();
    m_SpriteSheetManager->GetItemsTexture()->Draw(
        GetCollider()->GetCenterPosition() - Vector2f{40, 40},
        Rectf{1360, 0, 80,80}
    );
}
