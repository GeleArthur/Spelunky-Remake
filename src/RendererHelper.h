#pragma once

#include "Matrix.h"
#include "structs.h"

class RendererHelper {
public:
    static void Setup();
    static void DrawTexture(const Rectf& positionCoords, const Rectf& uvCoords);
    static void SetProjectionMatrix(float left, float right, float top, float bottom, float far, float near);
    static void PushMatrix();
    static void PopMatrix();
    static void TranslateMatrix(Vector2f translate);
    static void TranslateMatrix(float x, float y);
    static void ScaleMatrix(float x, float y);
    static void MultiMatrix(const Matrix4X4& matrixToMulti);
    static void IdentityMatrix();

private:
    static GLuint CreateShader();

    static Matrix4X4 m_ProjectionMatrix;
    static Matrix4X4 m_UserMatrix[32];
    static int m_UserMatrixIndex;
    static GLuint m_Program;
    static GLint m_matrixLocation;
    static GLuint m_vertexBuffer;
};

