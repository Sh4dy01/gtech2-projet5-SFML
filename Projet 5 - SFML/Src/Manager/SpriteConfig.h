#pragma once

#define SPRITE_SIZE 16
#define BASE_SCALE_FACTOR 4
#define BASE_TEXTURE_PATH "Assets/Sprites/"

#define PLAYER_NAME "Dave"
#define PLAYER_WALK_RECT                                                                                                      \
    {                                                                                                                            \
        sf::IntRect(1, 1, SPRITE_SIZE, SPRITE_SIZE), sf::IntRect(17, 17, SPRITE_SIZE, SPRITE_SIZE), sf::IntRect(34, 34, SPRITE_SIZE, SPRITE_SIZE), sf::IntRect(53, 53, SPRITE_SIZE, SPRITE_SIZE) \
    }