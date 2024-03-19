#include "pch.h"
#include "PlayerObject.h"

#include "SpriteSheetManager.h"
#include "Texture.h"

PlayerObject::PlayerObject(const Vector2f startPosition, SpriteSheetManager* spriteSheetManager):
    PhysicsObject(startPosition),
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
