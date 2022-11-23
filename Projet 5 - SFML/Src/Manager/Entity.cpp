#include "Entity.h"
#include "Manager/SpriteConfig.h"
#include <SFML/Graphics/Texture.hpp>

Entity::Entity(sf::String name, sf::Vector2f spawn) : name(name), pos(spawn)
{
}

void Entity::SetSprite(sf::IntRect rect)
{
	_texture.loadFromFile(BASE_TEXTURE_PATH + name + ".png", rect);
	_sprite.setTexture(_texture);
}
