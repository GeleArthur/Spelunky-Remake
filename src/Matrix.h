#pragma once
#ifdef __EMSCRIPTEN__
#include <SDL_opengles2.h>
#else
#include <glad/glad.h>
#endif
#include "Vector2f.h"

// Row major matrix
struct Matrix4X4 final
{
	void OpenGlArray(GLfloat (&array)[16]) const;
	void GlMultiMatrix() const;
	static Matrix4X4 IdentityMatrix();
	static Matrix4X4 TranslationMatrix(const Vector2f& position);
	static Matrix4X4 RotationMatrix(float rotation);
	static Matrix4X4 ScaleMatrix(float scale);
	static Matrix4X4 ScaleMatrix(float scaleX = 1, float scaleY = 1, float scaleZ = 1);
	static Matrix4X4 SkewMatrix(float yx = 1, float xy = 1);

	void PrintMatrix() const;
	Matrix4X4 operator*(const Matrix4X4& other) const;

	float m00;
	float m10;
	float m20;
	float m30;
	float m01;
	float m11;
	float m21;
	float m31;
	float m02;
	float m12;
	float m22;
	float m32;
	float m03;
	float m13;
	float m23;
	float m33;
};