#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/String.hpp>

class Entity : public sf::Sprite {

public:

	Entity(sf::String, bool isPokemon);
		/// <summary>
		/// Set the sprite, scale and spawn position of an entity
		/// </summary>
		/// <param name="region">Region to render the sprite from the atlas</param>
		/// <param name="scale">Add a scale to the BASE_SCALE_FACTOR which is 4</param>
	virtual void Initialize(sf::IntRect region, float scale, sf::Vector2i spawn);
	void SetSprite();
	void SetSpawn(sf::Vector2f spawn);

protected:

	bool isPokemon;

	sf::String name;
	sf::Texture _texture;
	float scale;
	float speed;
};