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

void CameraSystem::UpdateCamera()
{
    Vector2f cameraPos = m_Player->GetPosition();
    
    cameraPos.x = std::clamp(cameraPos.x, float(spelucky_settings::g_TileSize) * 10, float(spelucky_settings::g_TileSize) * (Cave::CAVE_TILE_COUNT_X - 10));
    cameraPos.y = std::clamp(cameraPos.y, float(spelucky_settings::g_TileSize) * 6, float(spelucky_settings::g_TileSize) * (Cave::CAVE_TILE_COUNT_Y - 6));
    
    cameraPos.x -= 1280/2; // TODO: Make screen size reference
    cameraPos.y -= 720/2;
    
    m_TranslateMatrix.m30 = -cameraPos.x;
    m_TranslateMatrix.m31 = -cameraPos.y;

    if(m_IsDebugCamera)
    {
        if(m_MouseDown)
        {
            m_DebugStartPoint = Vector2f{m_PrevMouse};
        }
    }
}

void CameraSystem::PushCamera() const
{
    glPushMatrix();
    m_TranslateMatrix.GlMultiMatrix();
    m_RotateMatrix.GlMultiMatrix();
    m_ScaleMatrix.GlMultiMatrix();

    if(m_IsDebugCamera)
    {
        m_DebugTranslateMatrix.GlMultiMatrix();
        m_DebugZoomMatrix.GlMultiMatrix();
    }
}

void CameraSystem::PopCamera()
{
    glPopMatrix();
}

Vector2f CameraSystem::GetCameraPosition() const
{
    return Vector2f{m_TranslateMatrix.m30, m_TranslateMatrix.m31};
}

void CameraSystem::EnableDebugCamera(const bool enabled)
{
    m_IsDebugCamera = enabled;
}

void CameraSystem::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
    if(m_MouseDown)
    {
        const Vector2f mouseMove = Vector2f(static_cast<float>(e.x), static_cast<float>(e.y)) - m_PrevMouse;
        m_DebugTranslateMatrix.m30 += mouseMove.x;
        m_DebugTranslateMatrix.m31 += mouseMove.y;
    }
    m_PrevMouse.x = static_cast<float>(e.x);
    m_PrevMouse.y = static_cast<float>(e.y);
}

void CameraSystem::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
    if(e.button == 1)
    {
        m_MouseDown = true;
    }
}

void CameraSystem::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
    m_MouseDown = false;
}

void CameraSystem::ProcessWheelEvent(const SDL_MouseWheelEvent& e)
{
    m_DebugZoomMatrix = m_DebugZoomMatrix * Matrix4X4::TranslationMatrix(Vector2f{(m_DebugTranslateMatrix.m30 + m_TranslateMatrix.m30) - e.mouseX, (m_DebugTranslateMatrix.m31 + m_TranslateMatrix.m31) - e.mouseY});
    m_DebugZoomMatrix.m33 -= e.preciseY*0.2f * m_DebugZoomMatrix.m33;
    m_DebugZoomMatrix = m_DebugZoomMatrix * Matrix4X4::TranslationMatrix(Vector2f{-((m_DebugTranslateMatrix.m30 + m_TranslateMatrix.m30) - e.mouseX), -((m_DebugTranslateMatrix.m31 + m_TranslateMatrix.m31) - e.mouseY)});
}
