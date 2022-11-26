#include "SoundManager.h"

#include <iostream>

void SoundManager::LoadSound(std::string name)
{
	if (!buffer->loadFromFile(BASE_SOUND_PATH + name + BASE_SOUND_EXTENSION))
		std::cout << name << " : sound file doesn't exist" << std::endl;
}
