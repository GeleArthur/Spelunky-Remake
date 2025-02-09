#include <SDL.h>
#ifdef __EMSCRIPTEN__
#include <SDL_opengles2.h>
#else
#include <glad/glad.h>
#endif
#include <SDL_ttf.h> 
#include <SDL_mixer.h> 
#include <SDL_image.h>

#include <iostream>
#include <algorithm>
#include "BaseGame.h"

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#ifndef NOMINMAX   /* don't define min() and max(). */
#define NOMINMAX
#endif
#include <windows.h>
#endif


BaseGame::BaseGame(const Window& window)
	: m_Window{ window }
	, m_Viewport{ 0,0,window.width,window.height }
	, m_pWindow{ nullptr }
	, m_pContext{ nullptr }
	, m_Initialized{ false }
	, m_MaxElapsedSeconds{ 0.1f }
{
	InitializeGameEngine();
}

BaseGame::~BaseGame()
{
	CleanupGameEngine();
}

void BaseGame::InitializeGameEngine()
{
	// disable console close window button
#ifdef _WIN32
	HWND hwnd = GetConsoleWindow();
	HMENU hmenu = GetSystemMenu(hwnd, FALSE);
	EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);
#endif

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO /*| SDL_INIT_AUDIO*/) < 0)
	{
		std::cerr << "BaseGame::Initialize( ), error when calling SDL_Init: " << SDL_GetError() << std::endl;
		return;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

	// Create window
	m_pWindow = SDL_CreateWindow(
		m_Window.title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		int(m_Window.width),
		int(m_Window.height),
		SDL_WINDOW_OPENGL);
	if (m_pWindow == nullptr)
	{
		std::cerr << "BaseGame::Initialize( ), error when calling SDL_CreateWindow: " << SDL_GetError() << std::endl;
		return;
	}

	// Create OpenGL context 
	m_pContext = SDL_GL_CreateContext(m_pWindow);
	if (m_pContext == nullptr)
	{
		std::cerr << "BaseGame::Initialize( ), error when calling SDL_GL_CreateContext: " << SDL_GetError() << std::endl;
		return;
	}

	#ifndef __EMSCRIPTEN__
	gladLoadGLES2Loader(SDL_GL_GetProcAddress); // 100% no documentation for this

	// Set the swap interval for the current OpenGL context,
	// synchronize it with the vertical retrace
	if (m_Window.isVSyncOn)
	{
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			std::cerr << "BaseGame::Initialize( ), error when calling SDL_GL_SetSwapInterval: " << SDL_GetError() << std::endl;
			return;
		}
	}
	else
	{
		SDL_GL_SetSwapInterval(0);
	}
	#endif


	// Set the Projection matrix to the identity matrix
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();

    // RendererHelper::SetProjectionMatrix(0, m_Window.width, -m_Window.height, 0, -1, 1);
	RendererHelper::Setup();
	RendererHelper::SetProjectionMatrix(0, -m_Window.width, 0, m_Window.height, -1, 1);
	// Set up a two-dimensional orthographic viewing region.
//	glOrtho(0, m_Window.width, m_Window.height, 0, -1, 1); // y from bottom to top

	// Set the viewport to the client window area
	// The viewport is the rectangular region of the window where the image is drawn.
	glViewport(0, 0, int(m_Window.width), int(m_Window.height));

	// Set the Modelview matrix to the identity matrix
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();

	// Enable color blending and use alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize PNG loading
	/*
	int imgFlags = IMG_INIT_PNG;
	if ( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		std::cerr << "BaseGame::Initialize( ), error when calling IMG_Init: " << IMG_GetError( ) << std::endl;
		return;
	}
	*/

	// Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cerr << "BaseGame::Initialize( ), error when calling TTF_Init: " << TTF_GetError() << std::endl;
		return;
	}

	//Initialize SDL_mixer
	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "BaseGame::Initialize( ), error when calling Mix_OpenAudio: " << Mix_GetError() << std::endl;
		return;
	}
	

	m_Initialized = true;
}

void BaseGame::Run()
{
	if (!m_Initialized)
	{
		std::cerr << "BaseGame::Run( ), BaseGame not correctly initialized, unable to run the BaseGame\n";
		std::cin.get();
		return;
	}


	t1 = std::chrono::steady_clock::now();
}

void BaseGame::MainLoop()
{
	SDL_Event e{};

	// Poll next event from queue
	while (SDL_PollEvent(&e) != 0)
	{
		// Handle the polled event
		switch (e.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			this->ProcessKeyDownEvent(e.key);
			break;
		case SDL_KEYUP:
			this->ProcessKeyUpEvent(e.key);
			break;
		case SDL_MOUSEMOTION:
			this->ProcessMouseMotionEvent(e.motion);
			break;
		case SDL_MOUSEWHEEL:
			this->ProcessWheelEvent(e.wheel);
		case SDL_MOUSEBUTTONDOWN:
			this->ProcessMouseDownEvent(e.button);
			break;
		case SDL_MOUSEBUTTONUP:
			this->ProcessMouseUpEvent(e.button);
			break;
		}
	}

	if (!quit)
	{
		std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
		float elapsedSeconds = std::chrono::duration<float>(t2 - t1).count();

		t1 = t2;
		elapsedSeconds = std::min(elapsedSeconds, m_MaxElapsedSeconds);

		this->Update(elapsedSeconds);
		this->Draw();

		SDL_GL_SwapWindow(m_pWindow);
	}
}
bool BaseGame::IsRunning()
{
	return !quit;
}

void BaseGame::CleanupGameEngine()
{
	SDL_GL_DeleteContext(m_pContext);

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;

	//Quit SDL subsystems
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();

	// enable console close window button
#ifdef _WIN32
	HWND hwnd = GetConsoleWindow();
	HMENU hmenu = GetSystemMenu(hwnd, FALSE);
	EnableMenuItem(hmenu, SC_CLOSE, MF_ENABLED);
#endif

}
