#pragma once
#include "BaseGame.h"
class Cave;
class SpriteSheetManager;

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game() override;

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessWheelEvent( const SDL_MouseWheelEvent& e ) override;

private:

	SpriteSheetManager* m_SpriteSheetManager;
	Cave* m_Cave;
	float m_TimeRunning{0};
	Vector2f m_QuickCamera{0,0};
	Vector2f m_PrevMouse{0,0};
	bool m_MouseDown{};
	Vector2f m_Zoom{1,1};

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};
