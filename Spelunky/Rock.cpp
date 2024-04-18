#include "pch.h"
#include "Rock.h"

#include "CirclePhysicsCollider.h"
#include "RectPhysicsCollider.h"
#include "SpriteSheetManager.h"
#include "Texture.h"


Rock::Rock(const Vector2f& position, const SpriteSheetManager* spriteSheetManager ,const std::vector<std::vector<Tile>>* tiles):
    RectPhysicsCollider(Rectf{position.x, position.y, 30, 30}),
    m_SpriteSheetManager(spriteSheetManager)
{
}

void Rock::Update(const float elapsedTime)
{
    // UpdatePhysics(elapsedTime);
}

void Rock::Draw() const
{
    // GetCollider()->DebugDraw();
    m_SpriteSheetManager->GetItemsTexture()->Draw(
        GetCenter() - Vector2f{40, 40},
        Rectf{1360, 0, 80,80}
    );
}

// TODO: rework physics so we dont reinterpret_cast everywhere
bool Rock::CanPickUp(const Collider* collider) const
{
    return false;
    // switch (collider->GetColliderType())
    // {
    // case ColliderTypes::circle:
    //     // TODO
    //     break;
    // case ColliderTypes::rect:
    //     if(collision_helpers::RectVsRectOverLab(*reinterpret_cast<const RectPhysicsCollider*>(GetCollider()), *reinterpret_cast<const RectPhysicsCollider*>(collider)))
    //     {
    //         return true;
    //     }
    //     break;
    // }
    // return false;
}

void Rock::Teleport(const Vector2f& position)
{
}

void Rock::Throw(const Vector2f& velocity)
{
}

bool Rock::IsPickedUp() const
{
    return m_IsPickedUp;
}

void Rock::SetIsPickedUp(const bool pickedUp)
{
    m_IsPickedUp = pickedUp;
}

