
#include "Bomb.h"

#include "Cave.h"
#include "EntityManager.h"
#include "Game.h"
#include "Vector2f.h"

#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Vector2i.h"
#include "WorldManager.h"


Bomb::Bomb(WorldManager* worldManager)
    : Entity(Rectf{0, 0, 34, 34}, 0, 5, 0.3f, true, worldManager),
    m_SpriteSheetManager(worldManager->GetSpriteSheet()),
    m_WorldManager{worldManager}
{
}

EntityType Bomb::GetEntityType() const
{
    return EntityType::bomb;
}

void Bomb::Draw() const
{
    if(IsDead()) return;
    glPushMatrix();
    glTranslatef(GetCenter().x, GetCenter().y, 0);

    int bombImage;
    const float invertTimer = TIMER_START - m_Timer;
    if(m_Timer < 0.2)
    {
        bombImage = 1+static_cast<int>(std::floor(invertTimer*invertTimer*10))%2;

        
    }
    else
    {
        bombImage = static_cast<int>(std::floor(invertTimer*invertTimer*5))%2;
    }
    
    m_SpriteSheetManager->GetItemsTexture()->Draw(
        Vector2f{-40, -40},
        Rectf{(5+bombImage)*80.0f, 3*80, 80,80}
    );

    glPopMatrix();
}

void Bomb::Update(const float elapsedTime)
{
    if(IsDead()) return;

    if(m_IsOnGround)
    {
        const Vector2f& velocity = m_PhysicsCollider.GetVelocity();
        const Vector2f newVelocity{
            std::max(std::abs(velocity.x) * 0.3f - 0.2f, 0.0f) * (velocity.x >= 0 ? 1.0f : -1.0f),
            std::max(std::abs(velocity.y) * 0.3f - 0.2f, 0.0f) * (velocity.y >= 0 ? 1.0f : -1.0f)
        };
        
        m_PhysicsCollider.SetVelocity(newVelocity);
    }
    
    Entity::Update(elapsedTime);

    const std::vector<std::pair<const Tile*, RayVsRectInfo>>& hitTiles = m_PhysicsCollider.GetTilesWeHit();

    m_IsOnGround = false;
    for (int i{}; i < hitTiles.size(); ++i)
    {
        switch (hitTiles[i].first->GetTileType())
        {
        case TileTypes::ground:
        case TileTypes::border:
            if(hitTiles[i].second.normal.y < 0)
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
    

    m_Timer -= elapsedTime;

    if(m_Timer < 0)
    {
        Explode();
    }
}

void Bomb::Throw(const Vector2f& position, const Vector2f& velocity)
{
    m_Health = 9999;
    m_PhysicsCollider.SetCenter(position);
    m_PhysicsCollider.SetVelocity(velocity);
    m_IsOnGround = false;
    m_Timer = TIMER_START;
}

void Bomb::Explode()
{
    m_Health = 0;

    const Vector2i center = Vector2i{GetCenter() / Game::TILE_SIZE};
    
    for (int x{-EXPLODE_RADIUS}; x < EXPLODE_RADIUS; ++x)
    {
        for (int y{-EXPLODE_RADIUS}; y < EXPLODE_RADIUS; ++y)
        {
            if(x*x + y*y <= EXPLODE_RADIUS*EXPLODE_RADIUS)
            {
                m_WorldManager->GetCave()->ExplodeTile(center + Vector2i{x, y});
            }
        }
    }

    const std::vector<Entity*>& entityRectColliders = m_WorldManager->GetEntityManager()->GetAllEntities();
    for (int i = 0; i < entityRectColliders.size(); ++i)
    {
        //TODO: Bombs should explode other bombs
        if((entityRectColliders)[i] == this) continue;
        
        const Vector2f difference = (entityRectColliders)[i]->GetCenter() - GetCenter();
        const float length = difference.Length();
        
        if(length < Game::TILE_SIZE*EXPLODE_RADIUS)
        {
            (entityRectColliders)[i]->YouGotHit(2, difference.Normalized() * 1.0f/length*30000 );
        }
    }
}

