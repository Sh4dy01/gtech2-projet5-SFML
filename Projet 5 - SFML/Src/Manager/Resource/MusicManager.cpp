#include "MusicManager.h"
#include <iostream>


MusicManager::MusicManager()
{
	music = new sf::Music();
	music->setVolume(50);
	music->setLoop(true);
}

MusicManager::~MusicManager()
{
	delete music;
}

bool MusicManager::IsMusicLoaded()
{
	if (!music)
		return false;
	else
		return true;
}

void MusicManager::LoadMusicAndPlay(std::string name)
{
	if (!music->openFromFile(BASE_MUSIC_PATH + name + BASE_MUSIC_EXTENSION))
		std::cout << name << " : music file doesn't exist" << std::endl;
	PlayMusic();
}

void MusicManager::PlayMusic()
{
	if (IsMusicLoaded())
		music->play();
}

void MusicManager::PauseCurrentMusic()
{
	if (IsMusicLoaded())
		music->pause();
}

void MusicManager::StopMusic()
{
	if (IsMusicLoaded())
		music->stop();
}
