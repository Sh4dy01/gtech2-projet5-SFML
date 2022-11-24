#pragma once

#define SPRITE_SIZE 16
#define BASE_SCALE_FACTOR 4
#define BASE_TEXTURE_PATH "Assets/Sprites/"
#define BASE_IMAGE_PATH "Assets/Images/"
#define BASE_FONT_PATH "Assets/Fonts/"

#define PLAYER_NAME "Dave"
#define PLAYER_ANIMATION \
{           \
    {/* WALK DOWN*/                                                                                                                       \
        sf::IntRect(0 * SPRITE_SIZE + 1, 0 * SPRITE_SIZE + 1, SPRITE_SIZE, SPRITE_SIZE), sf::IntRect(2 * SPRITE_SIZE + 3, 1, SPRITE_SIZE, SPRITE_SIZE) \
    },  \
    {/* WALK UP*/                                                                                                                       \
        sf::IntRect(3 * SPRITE_SIZE + 4, 0 * SPRITE_SIZE + 1, SPRITE_SIZE, SPRITE_SIZE), sf::IntRect(5 * SPRITE_SIZE + 6, 1, SPRITE_SIZE, SPRITE_SIZE) \
    },               \
    {/* WALK LEFT*/                                                                                                                       \
        sf::IntRect(6 * SPRITE_SIZE + 7, 0 * SPRITE_SIZE + 1, SPRITE_SIZE, SPRITE_SIZE), sf::IntRect(7 * SPRITE_SIZE + 8, 1, SPRITE_SIZE, SPRITE_SIZE) \
    },               \
    {/* WALK RIGHT*/                                                                                                                       \
        sf::IntRect(8 * SPRITE_SIZE + 9, 0 * SPRITE_SIZE + 1, SPRITE_SIZE, SPRITE_SIZE), sf::IntRect(9 * SPRITE_SIZE + 10, 1, SPRITE_SIZE, SPRITE_SIZE) \
    },               \
    {/* STAND UP*/                                                                                                                       \
        sf::IntRect(4 * SPRITE_SIZE + 5, 0 * SPRITE_SIZE + 1, SPRITE_SIZE, SPRITE_SIZE) \
    },               \
    {/* STAND DOWN*/                                                                                                                       \
        sf::IntRect(1 * SPRITE_SIZE + 2, 0 * SPRITE_SIZE + 1, SPRITE_SIZE, SPRITE_SIZE) \
    },               \
}