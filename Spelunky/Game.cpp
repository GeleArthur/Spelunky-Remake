#include "pch.h"
#include "Game.h"

#include <chrono>
#include <complex>
#include <iostream>
#include <ostream>

#include "CameraSystem.h"
#include "Cave.h"
#include "CirclePhysicsCollider.h"
#include "GizmosDrawer.h"
#include "GlobalValues.h"
#include "SpriteSheetManager.h"
#include "Matrix.h"
#include "PlayerObject.h"
#include "RectPhysicsCollider.h"
#include "Rock.h"
#include "Texture.h"
#include "utils.h"
#include "WorldManager.h"

float Game::currentTime{0};

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
	// Warning don't change order otherwise will crash.
	// I dont like that its not really clear what depends on what
	m_WorldManager = new WorldManager{};
	m_SpriteSheetManager = new SpriteSheetManager{m_WorldManager};
	m_Cave = new Cave{m_WorldManager};
	m_Player = new PlayerObject{m_WorldManager};
	m_ItemManager = new ItemManager{m_WorldManager};

	
	m_CameraSystem = new CameraSystem{m_Player};
	Reset();
}

void Game::Cleanup( )
{
	delete m_SpriteSheetManager;
	delete m_Cave;
	delete m_Player;
	delete m_ItemManager;
	delete m_WorldManager;
	delete m_CameraSystem;
	GizmosDrawer::Shutdown();
}

void Game::Update( float elapsedSec )
{
	currentTime += elapsedSec;
	m_Player->Update(elapsedSec);
	m_ItemManager->UpdateItems(elapsedSec);

	if(m_MouseDown)
	{
		m_DebugStartPoint = Vector2f{m_PrevMouse};
	}

	m_CameraSystem->UpdateCamera();

	m_PrevDeltaTime = elapsedSec;
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
	m_CameraSystem->PushCamera();
	
	// glPushMatrix();
	// m_MoveMatrix.GlMultiMatrix();
	// m_ZoomMatrix.GlMultiMatrix();

	// Background
	for (int x{}; x < 64*10*4/256; ++x)
	{
		for (int y{}; y < 64*8*4/256; ++y)
		{
			m_SpriteSheetManager->GetBackGroundTexture()->Draw(Vector2f{x*256.0f,y*256.f});
		}
	}
	
	m_Cave->Draw();
	m_ItemManager->DrawItems();
	m_Player->Draw();
	// m_ItemManager->DrawPickupItems();
	GizmosDrawer::SetColor({0,1.0f,0});
	GizmosDrawer::DrawQText(-m_CameraSystem->GetCameraPosition(), std::to_string((1/m_PrevDeltaTime)));
	GizmosDrawer::Draw();
	
	m_CameraSystem->PopCamera();
	// glPopMatrix();
}

void Game::Reset()
{
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
	m_Cave->GenerateLevel();
	m_ItemManager->ClearItems();
	float elapsedSeconds = std::chrono::duration<float>(std::chrono::steady_clock::now() - t2).count();
	std::cout << "Took: " << elapsedSeconds << " sec. To generate level";

	m_ItemManager->AddItem(new Rock{m_Cave->GetEntrance() + Vector2f{30, -64}, m_SpriteSheetManager, m_Cave->GetTiles()});
	m_Player->Respawn(m_Cave->GetEntrance() + Vector2f{SpeluckyGlobals::g_TileSize/2.0f,SpeluckyGlobals::g_TileSize/2.0f});
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent &e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	if(e.keysym.sym == SDLK_r)
	{
		Reset();
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
		m_MoveMatrix.m30 += mouseMove.x;
		m_MoveMatrix.m31 += mouseMove.y;
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
	m_ZoomMatrix = m_ZoomMatrix * Matrix4X4::TranslationMatrix(Vector2f{m_MoveMatrix.m30 - e.mouseX, m_MoveMatrix.m31 - e.mouseY});
	m_ZoomMatrix.m33 -= e.preciseY*0.2f * m_ZoomMatrix.m33;
	m_ZoomMatrix = m_ZoomMatrix * Matrix4X4::TranslationMatrix(Vector2f{-(m_MoveMatrix.m30 - e.mouseX), -(m_MoveMatrix.m31 - e.mouseY)});
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
