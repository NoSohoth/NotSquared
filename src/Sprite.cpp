#include <cmath>
#include "Sprite.hpp"


void Sprite::move(double dt)
{
    _x += _speed * cos(_direction) * dt;
    _y += _speed * (- sin(_direction)) * dt;
}


void Sprite::draw(sf::RenderWindow *win) const
{
    sf::Sprite sprite;
    sprite.setTexture(_texture);
    sprite.setTextureRect(sf::IntRect(_spriteXA,_spriteYA,_spriteXB,_spriteYB));
    sprite.setScale(sf::Vector2f(_scale, _scale));
    sprite.setPosition((int)_x, (int)_y);
    
    win->draw(sprite);
}
