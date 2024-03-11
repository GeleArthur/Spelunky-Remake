#include "pch.h"
#include "Matrix.h"
#include <cmath>
#include <iostream>

// Column major matrix
void Matrix4x4::OpenGlArray(GLfloat (&array)[16]) const
{
	array[0] =  m00;
	array[1] =  m01;
	array[2] =  m02;
	array[3] =  m03;
	
	array[4] =  m10;
	array[5] =  m11;
	array[6] =  m12;
	array[7] =  m13;
	
	array[8] =  m20;
	array[9] =  m21;
	array[10] = m22;
	array[11] = m23;
	
	array[12] = m30;
	array[13] = m31;
	array[14] = m32;
	array[15] = m33;
}

void Matrix4x4::GlMultiMatrix() const
{
	GLfloat glArray[16]{};
	OpenGlArray(glArray);
	glMultMatrixf(glArray);
}

Matrix4x4 Matrix4x4::IdentityMatrix()
{
	return Matrix4x4{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1,
	};
}

Matrix4x4 Matrix4x4::TranslationMatrix(const Vector2f& position)
{
	Matrix4x4 result{IdentityMatrix()};
	result.m30 = position.x;
	result.m31 = position.y;

	return result;
}

Matrix4x4 Matrix4x4::RotationMatrix(const float rotation)
{
	Matrix4x4 rotationMatrix{IdentityMatrix()};
	rotationMatrix.m00 = cos(rotation);
	rotationMatrix.m10 = -sin(rotation);
	rotationMatrix.m11 = cos(rotation);
	rotationMatrix.m01 = sin(rotation);
	
	return rotationMatrix;
}

Matrix4x4 Matrix4x4::ScaleMatrix(const float scale)
{
	Matrix4x4 scaleMatrix{IdentityMatrix()};
	scaleMatrix.m33 = 1.0f/scale; // Cool tick
	return scaleMatrix;
}

Matrix4x4 Matrix4x4::ScaleMatrix(const float scaleX, const float scaleY, const float scaleZ)
{
	Matrix4x4 scaleMatrix{IdentityMatrix()};
	scaleMatrix.m00 = scaleX;
	scaleMatrix.m11 = scaleY;
	scaleMatrix.m22 = scaleZ;
	return scaleMatrix;
}

Matrix4x4 Matrix4x4::SkewMatrix(const float yx, const float xy)
{
	Matrix4x4 skewMatrix{IdentityMatrix()};
	skewMatrix.m01 = yx;
	return skewMatrix;
}

void Matrix4x4::PrintMatrix() const
{
	std::cout << m00 << " " << m01 << " " << m02 << " " << m03 << std::endl;
	std::cout << m10 << " " << m11 << " " << m12 << " " << m13 << std::endl;
	std::cout << m20 << " " << m21 << " " << m22 << " " << m23 << std::endl;
	std::cout << m30 << " " << m31 << " " << m32 << " " << m33 << std::endl;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &other) const
{
	Matrix4x4 result;

	// Love
	
	result.m00 = this->m00 * other.m00 + this->m01 * other.m10 + this->m02 * other.m20 + this->m03 * other.m30;
	result.m01 = this->m00 * other.m01 + this->m01 * other.m11 + this->m02 * other.m21 + this->m03 * other.m31;
	result.m02 = this->m00 * other.m02 + this->m01 * other.m12 + this->m02 * other.m22 + this->m03 * other.m32;
	result.m03 = this->m00 * other.m03 + this->m01 * other.m13 + this->m02 * other.m23 + this->m03 * other.m33;

	result.m10 = this->m10 * other.m00 + this->m11 * other.m10 + this->m12 * other.m20 + this->m13 * other.m30;
	result.m11 = this->m10 * other.m01 + this->m11 * other.m11 + this->m12 * other.m21 + this->m13 * other.m31;
	result.m12 = this->m10 * other.m02 + this->m11 * other.m12 + this->m12 * other.m22 + this->m13 * other.m32;
	result.m13 = this->m10 * other.m03 + this->m11 * other.m13 + this->m12 * other.m23 + this->m13 * other.m33;

	result.m20 = this->m20 * other.m00 + this->m21 * other.m10 + this->m22 * other.m20 + this->m23 * other.m30;
	result.m21 = this->m20 * other.m01 + this->m21 * other.m11 + this->m22 * other.m21 + this->m23 * other.m31;
	result.m22 = this->m20 * other.m02 + this->m21 * other.m12 + this->m22 * other.m22 + this->m23 * other.m32;
	result.m23 = this->m20 * other.m03 + this->m21 * other.m13 + this->m22 * other.m23 + this->m23 * other.m33;

	result.m30 = this->m30 * other.m00 + this->m31 * other.m10 + this->m32 * other.m20 + this->m33 * other.m30;
	result.m31 = this->m30 * other.m01 + this->m31 * other.m11 + this->m32 * other.m21 + this->m33 * other.m31;
	result.m32 = this->m30 * other.m02 + this->m31 * other.m12 + this->m32 * other.m22 + this->m33 * other.m32;
	result.m33 = this->m30 * other.m03 + this->m31 * other.m13 + this->m32 * other.m23 + this->m33 * other.m33;

	return result;
}




