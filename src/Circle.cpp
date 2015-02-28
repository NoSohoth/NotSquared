#include <cmath>
#include "SFML/Graphics.hpp"
#include "Circle.hpp"

void Circle::move(double dt) 
{
	_x += _speed * cos(_direction) * dt;
    _y += _speed * (- sin(_direction)) * dt; //y axis points down
}

void Circle::draw(sf::RenderWindow *win) const
{
    sf::CircleShape circle(_height/2);
	int r, g, b;
    _color.getRGB(r, g, b); 
    circle.setFillColor(sf::Color(r, g, b));
    circle.setPosition((int)_x, (int)_y);
	circle.setOutlineColor(sf::Color(0, 0, 0));
	circle.setOutlineThickness(_height/15);
	win->draw(circle);
}
