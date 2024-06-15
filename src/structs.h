#pragma once
#include <string>
#include "Vector2f.h"

struct Window
{
	explicit Window( const std::string& title = "Title", float width = 320.0f, 
		float height = 180.0f, bool isVSyncOn = true );

	std::string title;
	float width;
	float height;
	bool isVSyncOn;
};

struct Rectf
{
	Rectf( );
	Rectf( float left, float bottom, float width, float height );
	Rectf operator+(Vector2f rhs) const;
	
	float left;
	float top;
	float width;
	float height;

};


struct Color4f
{
	Color4f( );
	Color4f( float r, float g, float b, float a = 1 );
	
	float r;
	float g;
	float b;
	float a;
	
	Color4f SetAlpha(float alpha) const;
};

struct Circlef
{
	Circlef( );
	explicit Circlef( const Vector2f& center, float radius );
	explicit Circlef( float centerX, float centerY, float radius );

	Vector2f center;
	float radius;
};


struct Ellipsef
{
	Ellipsef( );
	explicit Ellipsef( const Vector2f& center, float radiusX, float radiusY );
	explicit Ellipsef( float centerX, float centerY, float radiusX, float radiusY );

	Vector2f center;
	float radiusX;
	float radiusY;
};



