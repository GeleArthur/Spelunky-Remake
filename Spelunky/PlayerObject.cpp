#include "pch.h"
#include "PlayerObject.h"

#include <vector>

#include "CircleCollider.h"
#include "RectCollider.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "Tile.h"

PlayerObject::PlayerObject(SpriteSheetManager* spriteSheetManager, const std::vector<std::vector<Tile>>* tiles):
     PhysicsObject(new RectCollider{Rectf{0,0,64,64}}, tiles),
    m_SpriteSheetManager(spriteSheetManager)
{
}

void PlayerObject::Draw() const
{
    // TODO: animation system
    m_SpriteSheetManager->GetCurrentPlayerTexture()->Draw(GetCollider()->GetOrigin() - Vector2f{40,40}, Rectf{0,0,80,80});
    GetCollider()->DebugDraw();
}

void PlayerObject::Update(const float elapsedTimes)
{
    const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
    if ( pStates[SDL_SCANCODE_RIGHT] || pStates[SDL_SCANCODE_D] )
    {
        m_Velocity += Vector2f{10, 0};
    }
    if ( pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_A] )
    {
        m_Velocity += Vector2f{-10, 0};
    }
    if ( pStates[SDL_SCANCODE_UP] || pStates[SDL_SCANCODE_W] )
    {
        m_Velocity += Vector2f{0, -10};
    }
    if ( pStates[SDL_SCANCODE_DOWN] || pStates[SDL_SCANCODE_S] )
    {
        m_Velocity += Vector2f{0, 10};
    }
    
    UpdatePhysics(elapsedTimes);
}
