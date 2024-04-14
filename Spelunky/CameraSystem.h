#pragma once
#include "Matrix.h"

class PlayerObject;

class CameraSystem final
{
public:
    explicit CameraSystem(const PlayerObject* player);
    void UpdateCamera();
    void PushCamera();
    void PopCamera();
    Vector2f GetCameraPosition() const;

private:
    const PlayerObject* m_Player;
    Matrix4X4 m_TranslateMatrix{Matrix4X4::IdentityMatrix()};
    Matrix4X4 m_RotateMatrix{Matrix4X4::IdentityMatrix()};
    Matrix4X4 m_ScaleMatrix{Matrix4X4::IdentityMatrix()};
};
