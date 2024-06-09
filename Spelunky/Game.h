#pragma once
#include "BaseGame.h"
#include "InputManager.h"
#include "Matrix.h"
class UiManager;
class CameraSystem;
class EntityManager;
class WorldManager;
class PlayerObject;
class Cave;
class SpriteSheetManager;

class Game final : public BaseGame
{
public:
	explicit Game( const Window& window );
	~Game() override;
	
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;

	virtual void Update( float elapsedSec ) override;
	virtual void Draw( ) const override;
	void Reset() const;

	// Event handling
	virtual void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	virtual void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	virtual void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	virtual void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	virtual void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;
	virtual void ProcessWheelEvent( const SDL_MouseWheelEvent& e ) override;

	static constexpr int TILE_SIZE{64};
	
private:

	WorldManager* m_WorldManager;
	SpriteSheetManager* m_SpriteSheetManager;
	InputManager* m_InputManager;
	Cave* m_Cave;
	PlayerObject* m_Player;
	EntityManager* m_EntityManager;
	CameraSystem* m_CameraSystem;
	UiManager* m_UIManager;
	

	Matrix4X4 m_ZoomMatrix{Matrix4X4::IdentityMatrix()};
	Matrix4X4 m_MoveMatrix{Matrix4X4::IdentityMatrix()};

	float m_PrevDeltaTime{};
	float m_CurrentTime{};


	// FUNCTIONS
	void Cleanup( );
	void ClearBackground( ) const;
};
