#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <map>
#include <string>

#define BASE_SOUND_PATH "Assets/Audio/Sound/"
#define BASE_SOUND_EXTENSION ".wav"

class SoundManager {

public:

	SoundManager();

	void LoadSound(std::string fileName);
	void PlaySound(std::string fileName);
	void UnloadAllSounds();

	int GetVolume() { return sound->getVolume(); };
	void SetVolume(int volume) { sound->setVolume(volume); };

private:

	std::map<std::string, sf::SoundBuffer> sounds;
	sf::Sound* sound;
};