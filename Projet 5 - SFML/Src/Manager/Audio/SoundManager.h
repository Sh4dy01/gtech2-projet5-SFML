#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <string>

#define BASE_SOUND_PATH "Assets/Sound/"
#define BASE_SOUND_EXTENSION ".wav"

class SoundManager {

public:

	SoundManager();

	void LoadSound(std::string name);
	void PlaySound();

	void SetVolume(int volume) { sound->setVolume(volume); };

private:

	sf::SoundBuffer* buffer;
	sf::Sound* sound;
};