#pragma once
#include <SDL_opengl.h>
#include "Vector2f.h"

// Row major matrix
struct Matrix4x4
{
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

	void OpenGlArray(GLfloat (&array)[16]) const;
	void GlMultiMatrix() const;
	static Matrix4x4 IdentityMatrix();
	static Matrix4x4 TranslationMatrix(const Vector2f& position);
	static Matrix4x4 RotationMatrix(float rotation);
	static Matrix4x4 ScaleMatrix(float scale);
	static Matrix4x4 ScaleMatrix(float scaleX = 1, float scaleY = 1, float scaleZ = 1);
	static Matrix4x4 SkewMatrix(float yx = 1, float xy = 1);

	void PrintMatrix() const;
	Matrix4x4 operator*(const Matrix4x4& other) const;
};