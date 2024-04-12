#pragma once
#include "Matrix.h"

class PlayerObject;

class CameraSystem
{
public:
    explicit CameraSystem(const PlayerObject* player);
    virtual ~CameraSystem();
    void UpdateCamera();
    void PushCamera();
    void PopCamera();

private:
    const PlayerObject* m_Player;
    Matrix4X4 m_TranslateMatrix{Matrix4X4::IdentityMatrix()};
    Matrix4X4 m_RotateMatrix{Matrix4X4::IdentityMatrix()};
    Matrix4X4 m_ScaleMatrix{Matrix4X4::IdentityMatrix()};
};
