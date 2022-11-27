#pragma once
#include <SFML/Audio/Music.hpp>
#include <string>

#define BASE_MUSIC_PATH "Assets/Music/"
#define BASE_MUSIC_EXTENSION ".wav"

class MusicManager {

public:

	MusicManager();
	~MusicManager();

	bool IsMusicLoaded();

	void LoadMusicAndPlay(std::string name);
	void PlayMusic();
	void PauseCurrentMusic();
	void StopMusic();

	sf::Music* GetCurrentMusic() { return music; };
	int GetVolume() { return music->getVolume(); };

	void SetVolume(int volume) { music->setVolume(volume); };

private:

	sf::Music* music;
};