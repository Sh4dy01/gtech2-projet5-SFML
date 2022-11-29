#include "SoundManager.h"

#include <iostream>

SoundManager::SoundManager()
{
	sound = new sf::Sound();
	sound->setVolume(75);
}

void SoundManager::LoadSound(std::string fileName)
{
	auto elem = sounds.find(fileName);

	if (elem == sounds.end()) {
		std::string path = BASE_SOUND_PATH;
		path += fileName;
		path += BASE_SOUND_EXTENSION;

		sf::SoundBuffer snd;
		if (snd.loadFromFile(path)) {
			sounds.insert(std::pair<std::string, sf::SoundBuffer&>(fileName, snd)).first->second;
			std::cout << path << " loaded" << std::endl;
		}
	}
	else {
		std::cout << fileName << " already exist !" << std::endl;
	}
}

void SoundManager::PlaySound(std::string fileName)
{
	auto elem = sounds.find(fileName);

	if (elem != sounds.end())
	{
		sound->setBuffer(elem->second);
		sound->play();
		std::cout << fileName << " played !" << std::endl;
	}
	else {
		std::cout << fileName << " isn't loaded !" << std::endl;
	}
}

void SoundManager::UnloadAllSounds() {
	sounds.clear();
	std::cout << "Unloaded all sounds !" << std::endl;
}
