#pragma once
#include "Matrix.h"

class PlayerObject;

class CameraSystem final
{
public:
    explicit CameraSystem(const PlayerObject* player);
    virtual ~CameraSystem() = default;
    CameraSystem(const CameraSystem& other) = delete;
    CameraSystem& operator=(const CameraSystem& other) = delete;
    CameraSystem(CameraSystem && other) = delete;
    CameraSystem& operator=(CameraSystem&& other) = delete;
    
    void UpdateCamera();
    void PushCamera() const;
    void PopCamera();
    Vector2f GetCameraPosition() const;
    
    void EnableDebugCamera(bool enabled);
    void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
    void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
    void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );
    void ProcessWheelEvent(const SDL_MouseWheelEvent& e);

private:
    const PlayerObject* m_Player;
    Matrix4X4 m_TranslateMatrix{Matrix4X4::IdentityMatrix()};
    Matrix4X4 m_RotateMatrix{Matrix4X4::IdentityMatrix()};
    Matrix4X4 m_ScaleMatrix{Matrix4X4::IdentityMatrix()};


    
    bool m_IsDebugCamera{false};
    bool m_MouseDown{false};
    Vector2f m_DebugStartPoint{};
    Vector2f m_PrevMouse{0,0};
    Matrix4X4 m_DebugTranslateMatrix{Matrix4X4::IdentityMatrix()};
    Matrix4X4 m_DebugZoomMatrix{Matrix4X4::IdentityMatrix()};
};
