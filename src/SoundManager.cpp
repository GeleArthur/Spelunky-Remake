#include "pch.h"
#include "SoundManager.h"

#include "WorldManager.h"
SoundManager::SoundManager(WorldManager* worldManager):
	m_Music(Mix_LoadMUS("ALLSOUNDS/A01_A.wav")),
	m_WhipEffect(Mix_LoadWAV("ALLSOUNDS/whip.wav")),
	m_PickUpEffect(Mix_LoadWAV("ALLSOUNDS/pickup.wav")),
	m_ThrowItemEffect(Mix_LoadWAV("ALLSOUNDS/throw_item.wav")),
	m_DropItemEffect(Mix_LoadWAV("ALLSOUNDS/item_drop.wav")),
	m_HitEffect(Mix_LoadWAV("ALLSOUNDS/hit.wav")),
	m_LandEffect(Mix_LoadWAV("ALLSOUNDS/land.wav"))
{
	Mix_MasterVolume(32);
	Mix_PlayMusic(m_Music, -1);
	Mix_VolumeMusic(32);
	worldManager->SetSoundManager(this);
}
SoundManager::~SoundManager()
{
	Mix_FreeChunk(m_WhipEffect);
	Mix_FreeChunk(m_PickUpEffect);
	Mix_FreeChunk(m_ThrowItemEffect);
	Mix_FreeChunk(m_DropItemEffect);
	Mix_FreeChunk(m_HitEffect);
	Mix_FreeChunk(m_LandEffect);
	
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
	case SoundEffectTypes::throwItem:
		Mix_PlayChannel(-1, m_ThrowItemEffect, 0);
		break;
	case SoundEffectTypes::dropItem:
		Mix_PlayChannel(-1, m_DropItemEffect, 0);
		break;
	case SoundEffectTypes::hit:
		Mix_PlayChannel(-1, m_HitEffect, 0);
		break;
	case SoundEffectTypes::land:
		Mix_PlayChannel(-1, m_LandEffect, 0);
		break;
	}
}
