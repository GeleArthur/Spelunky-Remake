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
	glTranslatef(m_QuickCamera.x, m_QuickCamera.y, 0);
	glScalef(m_Zoom.x, m_Zoom.y, 1);

	for (int x{}; x < 64*10*4/256.0f; ++x)
	{
		for (int y{}; y < 64*8*4/256.0f; ++y)
		{
			m_SpriteSheetManager->GetBackGroundTexture()->Draw(Vector2f{x*256.0f,y*256.f});
		}
	}

	//Matrix4x4::TranslationMatrix(Vector2f{150, 150}).GlMultiMatrix();
	//Matrix4x4::RotationMatrix(m_TimeRunning).GlMultiMatrix();
	//Matrix4x4::SkewMatrix(sin(m_TimeRunning)).GlMultiMatrix();
	//Matrix4x4::TranslationMatrix(Vector2f{-150, -150}).GlMultiMatrix();
	//m_SpriteSheetManager->GetSingleton()->m_LevelTexture->Draw(Vector2f{0,0}, Rectf{0,64,64,64});


	m_Cave->Draw();

	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent &e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	if(e.keysym.sym == SDLK_r)
	{
		delete m_Cave;
		m_Cave = new Cave{};
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
	if(m_MouseDown)
	{
		const Vector2f mouseMove = Vector2f(static_cast<float>(e.x), static_cast<float>(e.y)) - m_PrevMouse;
		m_QuickCamera += mouseMove;
	}
	m_PrevMouse.x = static_cast<float>(e.x);
	m_PrevMouse.y = static_cast<float>(e.y);
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	if(e.button == 1)
	{
		m_MouseDown = true;
	}
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
	m_MouseDown = false;
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

void Game::ProcessWheelEvent(const SDL_MouseWheelEvent& e)
{
	m_Zoom.x += e.preciseY*0.2f * m_Zoom.x;
	m_Zoom.y += e.preciseY*0.2f * m_Zoom.y;

	std::cout << m_Zoom.x << '\n';
}

void Game::ClearBackground( ) const
{
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
