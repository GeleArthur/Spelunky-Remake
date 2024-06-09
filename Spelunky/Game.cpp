#include "pch.h"
#include "Game.h"

#include <assert.h>
#include <chrono>
#include <complex>
#include <iostream>
#include <ostream>

#include "Bat.h"
#include "CameraSystem.h"
#include "Cave.h"
#include "EntityManager.h"
#include "GizmosDrawer.h"

#include "InputManager.h"
#include "Matrix.h"
#include "PlayerObject.h"
#include "RectPhysicsCollider.h"
#include "SoundManager.h"
#include "SpriteSheetManager.h"
#include "Texture.h"
#include "UIManager.h"
#include "WorldManager.h"

Game::Game(const Window& window):
    BaseGame{window},
    m_WorldManager(new WorldManager{}),
    m_SpriteSheetManager(new SpriteSheetManager{m_WorldManager}),
    m_InputManager(new InputManager{m_WorldManager}),
    m_SoundManager(new SoundManager{m_WorldManager}),
    m_Cave(new Cave{m_WorldManager}),
    m_Player(new PlayerObject{m_WorldManager}),
    m_EntityManager(new EntityManager{m_WorldManager}),
    m_CameraSystem(new CameraSystem{m_Player}),
    m_UiManager(new UiManager{m_WorldManager})
{
    GizmosDrawer::SetTimePointer(&m_CurrentTime);
    Reset();
}

Game::~Game()
{
    Cleanup();
}

void Game::Cleanup()
{
    delete m_SpriteSheetManager;
    delete m_Cave;
    delete m_Player;
    delete m_EntityManager;
    delete m_WorldManager;
    delete m_CameraSystem;
    delete m_InputManager;
    delete m_UiManager;
    delete m_SoundManager;
    GizmosDrawer::Shutdown();
}

void Game::Update(const float elapsedSec)
{
    m_CurrentTime += elapsedSec;
    m_InputManager->Update();
    m_Player->Update(elapsedSec);
    m_EntityManager->UpdateEntity(elapsedSec);

    m_CameraSystem->UpdateCamera(elapsedSec);

    if(m_Player->GetPlayerState() == PlayerState::dead || m_Player->GetPlayerState() == PlayerState::enteringLeaving)
    {
        Reset();
    }
    
    m_PrevDeltaTime = elapsedSec;

    if(m_InputManager->PressingSecretCode())
    {
        m_CameraSystem->EnableDebugCamera(true);
    }
    
    // GizmosDrawer::SetColor({0, 1.0f, 0});
    // GizmosDrawer::DrawQText(-m_CameraSystem->GetCameraPosition(), std::to_string((1 / m_PrevDeltaTime)));

    
    
}

void Game::Draw() const
{
    ClearBackground();

    m_CameraSystem->PushCamera();

    // Background
    for (int x{}; x < 64 * 10 * 4 / 256; ++x)
    {
        for (int y{}; y < 64 * 8 * 4 / 256; ++y)
        {
            m_SpriteSheetManager->GetBackGroundTexture()->Draw(Vector2f{
                Game::TILE_SIZE * 2 + x * 256.0f, Game::TILE_SIZE * 2 + y * 256.f
            });
        }
    }

    m_Cave->Draw();
    m_EntityManager->DrawEntities();
    m_Player->Draw();

    if(m_Player->CanPlayerLeave())
    {
        const Rectf location{m_Cave->GetExit().x - 32*0.3f, m_Cave->GetExit().y - 64, 64*2 * 0.7f , 64 * 0.7f};
        m_SpriteSheetManager->GetHudElementTexture()->Draw(location, Rectf{64, 9*64,64,64});
        m_SpriteSheetManager->GetSpaceText()->Draw(Vector2f{location.left+10, location.top});
    }
    
    GizmosDrawer::Draw();
    m_CameraSystem->PopCamera();

    m_UiManager->Draw();
}

void Game::Reset() const
{
    const std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    m_Cave->GenerateLevel();
    const float elapsedSeconds = std::chrono::duration<float>(std::chrono::steady_clock::now() - t2).count();
    std::cout << "Took: " << elapsedSeconds << " sec. To generate level";

    m_EntityManager->ClearAllEntities();
    m_EntityManager->AddEntity(m_Player);
    m_EntityManager->GenerateEntities();
    m_Player->Respawn(m_Cave->GetEntrance() + Vector2f{TILE_SIZE / 2.0f, TILE_SIZE / 2.0f});
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
    //std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
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

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
    m_CameraSystem->ProcessMouseMotionEvent(e);
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
    m_CameraSystem->ProcessMouseDownEvent(e);
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

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
    m_CameraSystem->ProcessMouseUpEvent(e);
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
    m_CameraSystem->ProcessWheelEvent(e);
}

void Game::ClearBackground() const
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
