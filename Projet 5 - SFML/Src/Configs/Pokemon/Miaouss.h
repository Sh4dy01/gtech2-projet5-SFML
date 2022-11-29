#pragma once

#define MIAOUSS_SIZE 23

#define MIAOUSS_ANIMATION \
{   \
    {/* WALK DOWN*/   \
        sf::IntRect(1 * MIAOUSS_SIZE, 0 * MIAOUSS_SIZE, MIAOUSS_SIZE, MIAOUSS_SIZE), \
        sf::IntRect(1 * MIAOUSS_SIZE, 1 * MIAOUSS_SIZE, MIAOUSS_SIZE, MIAOUSS_SIZE) \
    }, \
    {/* WALK UP*/   \
        sf::IntRect(0 * MIAOUSS_SIZE, 0 * MIAOUSS_SIZE, MIAOUSS_SIZE, MIAOUSS_SIZE),\
        sf::IntRect(0 * MIAOUSS_SIZE, 1 * MIAOUSS_SIZE, MIAOUSS_SIZE, MIAOUSS_SIZE) \
    }, \
    {/* WALK RIGHT*/   \
        sf::IntRect(2 * MIAOUSS_SIZE, 0 * MIAOUSS_SIZE, MIAOUSS_SIZE, MIAOUSS_SIZE), \
        sf::IntRect(2 * MIAOUSS_SIZE, 1 * MIAOUSS_SIZE, MIAOUSS_SIZE, MIAOUSS_SIZE) \
    }           \
}   