#include "pch.h"
#include "Entity.h"

#include "SoundManager.h"
#include "Tile.h"
#include "WorldManager.h"

Entity::Entity(const Rectf& collider, const int health, const float mass, const float bounciness, bool invisible, WorldManager* worldManager):
    m_Health(health),
    m_Invisable(invisible),
    m_PhysicsCollider(collider, mass, bounciness, worldManager),
    m_SoundManager(worldManager->GetSoundManager())
{
}

void Entity::Update(const float elapsedTime)
{
    if(IsDead()) return;
    
    m_PhysicsCollider.ApplyForce(Vector2f{0,1000} * elapsedTime);
    m_PhysicsCollider.UpdatePhysics(elapsedTime);

    if(m_Invisable) return;
    const std::vector<std::pair<const Tile*, RayVsRectInfo>>& tiles = m_PhysicsCollider.GetTilesWeHit();
    for (const std::pair<const Tile*, RayVsRectInfo> tile : tiles)
    {
        if(tile.first->GetTileType() == TileTypes::spikes)
        {
            if(m_PhysicsCollider.GetVelocity().y > 0)
            {
                m_Health -= 100;
            }
        }
    }
}

void Entity::YouGotHit(const int damage, const Vector2f& force)
{
    m_SoundManager->PlaySoundEffect(SoundEffectTypes::hit);

    if(m_Invisable) return;
    m_Health -= damage;
    m_PhysicsCollider.ApplyForce(force);


    // Spawn Blood particle
}
int Entity::GetHealth() const
{
    return m_Health;
}

bool Entity::IsDead() const
{
    return m_Health <= 0;
}
const Rectf& Entity::GetRect() const
{
    return m_PhysicsCollider.GetRect();
}
Vector2f Entity::GetCenter() const
{
    return m_PhysicsCollider.GetCenter();
}
const RectPhysicsCollider& Entity::GetCollider() const
{
    return m_PhysicsCollider;
}



void Entity::Throw(const Vector2f& force)
{
}
bool Entity::TryToPickUp(Entity* pickedUpBy)
{
    return false;
}
void Entity::SetTargetPosition(const Vector2f& position, const Vector2f& goingTo)
{
}
bool Entity::IsPickedUp() const
{
    return false;
}
bool Entity::CanBePickedUp() const
{
    return false;
}

