#include "Texture.hpp"

void Texture::draw(sf::RenderWindow *win) const
{
	sf::Sprite sprite;
	sprite.setTexture(_texture);
	sprite.setPosition((int)_x, (int)_y);
	
	win->draw(sprite);
}
