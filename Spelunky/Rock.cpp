#include "pch.h"
#include "Rock.h"

#include "CirclePhysicsCollider.h"
#include "RectPhysicsCollider.h"
#include "SpriteSheetManager.h"
#include "Texture.h"


Rock::Rock(const Vector2f& position, const SpriteSheetManager* spriteSheetManager ,const std::vector<std::vector<Tile>>* tiles):
    PhysicsObject(new RectPhysicsCollider{Rectf{position.x,position.y,30,30}}, tiles),
    m_SpriteSheetManager(spriteSheetManager)
{
}

void Rock::Update(const float elapsedTime)
{
    if(!m_IsPickedUp)
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

// TODO: rework physics so we dont reinterpret_cast everywhere
bool Rock::CanPickUp(const Collider* collider) const
{
    switch (collider->GetColliderType())
    {
    case ColliderTypes::circle:
        // TODO
        break;
    case ColliderTypes::rect:
        if(collision_helpers::RectVsRectOverLab(*reinterpret_cast<const RectPhysicsCollider*>(GetCollider()), *reinterpret_cast<const RectPhysicsCollider*>(collider)))
        {
            return true;
        }
        break;
    }
    return false;
}

bool Rock::IsPickedUp() const
{
    return m_IsPickedUp;
}

void Rock::Teleport(const Vector2f& position)
{
    m_Collider->SetOrigin(position);
}

void Rock::Throw(const Vector2f& velocity)
{
    m_Velocity = velocity;
}

void Rock::SetIsPickedUp(const bool pickedUp)
{
    m_IsPickedUp = pickedUp;
}
