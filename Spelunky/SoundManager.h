#pragma once
#include "SoundEffectTypes.h"


class WorldManager;
class SoundManager final
{
public:
	SoundManager(WorldManager* worldManager);
	~SoundManager();
	SoundManager( const SoundManager& other ) = delete;
	SoundManager& operator=( const SoundManager& rhs ) = delete;
	SoundManager(SoundManager&& other) = delete;
	SoundManager& operator=(SoundManager&& other) = delete;

	void PlaySoundEffect(SoundEffectTypes type) const;
	
private:
	Mix_Music* m_Music;
	Mix_Chunk* m_WhipEffect;
	Mix_Chunk* m_PickUpEffect;
};
