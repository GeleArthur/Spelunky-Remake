#include "pch.h"
#include "SoundManager.h"

#include "SoundStream.h"
#include "WorldManager.h"
SoundManager::SoundManager(WorldManager* worldManager):
	m_Music(Mix_LoadMUS("ALLSOUNDS/A01_A.wav")),
	m_WhipEffect(Mix_LoadWAV("ALLSOUNDS/whip.wav")),
	m_PickUpEffect(Mix_LoadWAV("ALLSOUNDS/pickup.wav"))
{
	Mix_MasterVolume(32);
	Mix_PlayMusic(m_Music, -1);
	Mix_VolumeMusic(32);
	worldManager->SetSoundManager(this);
}
SoundManager::~SoundManager()
{
	Mix_FreeChunk(m_WhipEffect);
	Mix_FreeMusic(m_Music);
}
void SoundManager::PlaySoundEffect(const SoundEffectTypes type) const
{
	switch (type)
	{
	case SoundEffectTypes::whip:
		Mix_PlayChannel(-1, m_WhipEffect, 0);
		break;
	case SoundEffectTypes::pickup:
		Mix_PlayChannel(-1, m_PickUpEffect, 0);
		break;
	case SoundEffectTypes::hurt:
		break;
	}
}
