#include "pch.h"
#include "Game.h"

#include <iostream>
#include <ostream>

#include "Cave.h"
#include "SpriteSheetManager.h"
#include "Matrix.h"
#include "Texture.h"


Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();

}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_SpriteSheetManager = new SpriteSheetManager{};
	m_Cave = new Cave{};
}

void Game::Cleanup( )
{
	delete m_SpriteSheetManager;
	delete m_Cave;
}

void Game::Update( float elapsedSec )
{
	m_TimeRunning += elapsedSec;
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground( );


	glPushMatrix();
	//Matrix4x4::TranslationMatrix(Vector2f{150, 150}).GlMultiMatrix();
	//Matrix4x4::RotationMatrix(m_TimeRunning).GlMultiMatrix();
	//Matrix4x4::SkewMatrix(sin(m_TimeRunning)).GlMultiMatrix();
	//Matrix4x4::TranslationMatrix(Vector2f{-150, -150}).GlMultiMatrix();

	m_SpriteSheetManager->GetSingleton()->m_LevelTexture->Draw(Vector2f{0,0}, Rectf{0,0,2048,2048});
	//m_Cave->Draw();

	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent &e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	if(e.keysym.sym == SDLK_r)
	{
		m_Cave->CreateRoom();
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
