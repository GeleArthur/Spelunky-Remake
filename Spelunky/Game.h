#pragma once
#include "BaseGame.h"
#include "Matrix.h"
class CameraSystem;
class EntityManager;
class WorldManager;
class PlayerObject;
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
	void Reset();

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessWheelEvent( const SDL_MouseWheelEvent& e ) override;

	static float currentTime; // TODO: Move this
	
private:

	SpriteSheetManager* m_SpriteSheetManager;
	Cave* m_Cave;
	PlayerObject* m_Player;
	WorldManager* m_WorldManager;
	EntityManager* m_EntityManager;
	CameraSystem* m_CameraSystem;

	Vector2f m_DebugStartPoint{};
	Vector2f m_PrevMouse{0,0};
	bool m_MouseDown{};
	Matrix4X4 m_ZoomMatrix{Matrix4X4::IdentityMatrix()};
	Matrix4X4 m_MoveMatrix{Matrix4X4::IdentityMatrix()};

	float m_PrevDeltaTime;

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};
