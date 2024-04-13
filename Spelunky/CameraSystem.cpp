#include "pch.h"
#include "CameraSystem.h"
#include "PlayerObject.h"
#include <algorithm>

#include "Game.h"
#include "GlobalValues.h"
#include "Cave.h"

CameraSystem::CameraSystem(const PlayerObject* player):
    m_Player(player)
{
}

CameraSystem::~CameraSystem()
{
}

void CameraSystem::UpdateCamera()
{
    Vector2f cameraPos = m_Player->GetCollider()->GetOrigin();
    
    cameraPos.x = std::clamp(cameraPos.x, float(SpeluckyGlobals::g_TileSize) * 8, float(SpeluckyGlobals::g_TileSize) * (Cave::MAX_CAVE_TILE_COUNT_X - 8));
    cameraPos.y = std::clamp(cameraPos.y, float(SpeluckyGlobals::g_TileSize) * 4, float(SpeluckyGlobals::g_TileSize) * (Cave::MAX_CAVE_TILE_COUNT_X - 8));
    
    cameraPos.x -= 1280/2; // TODO: Make screen size reference
    cameraPos.y -= 720/2;
    
    m_TranslateMatrix.m30 = -cameraPos.x;
    m_TranslateMatrix.m31 = -cameraPos.y;
}

void CameraSystem::PushCamera()
{
    glPushMatrix();
    m_TranslateMatrix.GlMultiMatrix();
    m_RotateMatrix.GlMultiMatrix();
    m_ScaleMatrix.GlMultiMatrix();
}

void CameraSystem::PopCamera()
{
    glPopMatrix();
}

Vector2f CameraSystem::GetCameraPosition() const
{
    return Vector2f{m_TranslateMatrix.m30, m_TranslateMatrix.m31};
}
