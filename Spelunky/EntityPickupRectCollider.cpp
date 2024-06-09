#include "pch.h"
#include "EntityPickupRectCollider.h"

#include "GizmosDrawer.h"
#include "Tile.h"
#include "TileTypes.h"
// #include "Tile.h"

EntityPickupRectCollider::EntityPickupRectCollider(const Rectf& collider, const int health, const float mass, const float bounciness, bool invisible, WorldManager* worldManager):
    Entity(collider, health, mass, bounciness, invisible, worldManager)
{
}

void EntityPickupRectCollider::Update(const float elapsedTime)
{
    if(IsDead()) return;
    m_IsOnGround = false;
    if(m_PickedUpBy != nullptr)
    {
        GizmosDrawer::DrawCircle(m_CenterOfTarget, 10);
        GizmosDrawer::DrawCircle(m_GoingToPosition, 20);
        m_PhysicsCollider.SetCenter(m_CenterOfTarget);
        m_PhysicsCollider.SetVelocity((m_GoingToPosition - m_CenterOfTarget) / elapsedTime );
        m_PhysicsCollider.UpdatePhysics(elapsedTime);
    }
    else
    {
        Entity::Update(elapsedTime);

        EntitiesWeHitCheck(m_PhysicsCollider.GetEntitiesWeHit());
        TilesWeHitCheck(m_PhysicsCollider.GetTilesWeHit());
    }
}

void EntityPickupRectCollider::Throw(const Vector2f& force)
{
    m_HitPrevFrame.push_back(m_PickedUpBy);
    m_PickedUpBy = nullptr;

    m_PhysicsCollider.SetVelocity(force);
}

bool EntityPickupRectCollider::TryToPickUp(Entity* pickedUpBy)
{
    if(CanBePickedUp())
    {
        m_PickedUpBy = pickedUpBy;
        m_HitPrevFrame.clear();
        
        return true;
    }
    return false;
}

void EntityPickupRectCollider::SetTargetPosition(const Vector2f& position, const Vector2f& goingTo)
{
    m_CenterOfTarget = position;
    m_GoingToPosition = goingTo;
}

bool EntityPickupRectCollider::IsPickedUp() const
{
    return m_PickedUpBy != nullptr;
}

bool EntityPickupRectCollider::CanBePickedUp() const
{
    return m_IsOnGround;
}

bool EntityPickupRectCollider::IsOnGround() const
{
    return m_IsOnGround;
}

void EntityPickupRectCollider::TilesWeHitCheck(const std::vector<std::pair<const Tile*, RayVsRectInfo>>& hitInfo)
{
    for (int i{}; i < hitInfo.size(); ++i)
    {
        switch (hitInfo[i].first->GetTileType())
        {
        case TileTypes::ground:
        case TileTypes::border:
            if(hitInfo[i].second.normal.y < 0)
            {
                m_IsOnGround = true;
            }
         break;
        case TileTypes::air:
        case TileTypes::ladderTop:
        case TileTypes::ladder:
        case TileTypes::spikes:
        case TileTypes::pushBlock:
        case TileTypes::entrance:
        case TileTypes::exit:
        case TileTypes::unknown:
            break;
        }
    }
}

void EntityPickupRectCollider::EntitiesWeHitCheck(const std::vector<std::pair<RayVsRectInfo, Entity*>>& hitInfo)
{
    if(!IsOnGround() && !IsPickedUp() )
    {
        if(m_PhysicsCollider.GetVelocity().SquaredLength() > 450*450)
        {
            std::vector<Entity*> entitiesHitNow{hitInfo.size()};
            
            for (int i{}; i < hitInfo.size(); ++i)
            {
                entitiesHitNow.push_back(hitInfo[i].second);

                bool alReadyHit{false};
                for (int j{}; j < m_HitPrevFrame.size(); ++j)
                {
                    if(m_HitPrevFrame[j] == hitInfo[i].second)
                    {
                        alReadyHit = true;
                        break;
                    }
                }
                
                if(alReadyHit) continue;
                hitInfo[i].second->YouGotHit(1, m_PhysicsCollider.GetVelocity());
            }

            m_HitPrevFrame = entitiesHitNow; // ?? Copy Assignment constructor
        }
    }
}
