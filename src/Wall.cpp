#include "Wall.hpp"

void Wall::draw(sf::RenderWindow *win) const
{
    sf::RectangleShape wall(sf::Vector2f(_width, _height));
    int r, g, b;
    _color.getRGB(r, g, b);
    wall.setFillColor(sf::Color(r, g, b));
    wall.setPosition((int)_x, (int)_y);
    win->draw(wall);
}
