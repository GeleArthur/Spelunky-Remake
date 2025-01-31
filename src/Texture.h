#pragma once
#include <SDL_ttf.h>
#include <SDL.h>

#ifdef __EMSCRIPTEN__
#include <SDL_opengles2.h>
#else
#include <glad/glad.h>
#endif

#include "structs.h"
#include "Vector2f.h"

class Texture final
{
public:
	explicit Texture( const std::string& imagePath );
	explicit Texture( const std::string& text, TTF_Font *pFont, const Color4f& textColor );
	explicit Texture( const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor );
	Texture( const Texture& other ) = delete;
	Texture& operator=( const Texture& other ) = delete;
	Texture( Texture&& other ) noexcept;
	Texture& operator=( Texture&& other ) noexcept;
	~Texture();

	void Draw(const Vector2f& dstTopLeft = {}, const Rectf& srcRect = {}) const;
	void Draw( const Rectf& dstRect, const Rectf& srcRect = {} ) const;

	float GetWidth() const;
	float GetHeight() const;
	bool IsCreationOk( ) const;

private:
	//DATA MEMBERS
	GLuint m_Id;
	float m_Width;
	float m_Height;
	bool m_CreationOk;

	// FUNCTIONS
	void CreateFromImage( const std::string& path );
	void CreateFromString( const std::string& text, TTF_Font *pFont, const Color4f& textColor );
	void CreateFromString( const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor );
	void CreateFromSurface(const SDL_Surface *pSurface );
//	void DrawFilledRect(const Rectf& dstRect) const;
};
