#include "Sprite.hpp"

void Sprite::draw(sf::RenderWindow *win) const
{
	sf::Sprite sprite;
	sprite.setTexture(_texture);
	sprite.setTextureRect(sf::IntRect(_spriteXA,_spriteYA,_spriteXB,_spriteYB));
	sprite.setScale(sf::Vector2f(_scale, _scale));
	sprite.setPosition((int)_x, (int)_y);
	
	win->draw(sprite);
}
