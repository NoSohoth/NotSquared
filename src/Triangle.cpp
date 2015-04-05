#include <cmath>
#include "Triangle.hpp"
#include "Pong.hpp"


void Triangle::move(double dt)
{
    _x += (double) (_speed) * cos(_direction) * dt;
    _y += (double) (_speed) * (- sin(_direction)) * dt; //y axis points down
}

void Triangle::draw(sf::RenderWindow *win) const
{
    sf::CircleShape triangle(_height/2, 3);
    int r, g, b;
    _color.getRGB(r, g, b);
    triangle.setFillColor(sf::Color(r, g, b));
    triangle.setPosition((int)_x, (int)_y);
    triangle.setOrigin(_width/2, _height/2);
    triangle.setRotation(- _orientation*180 / M_PI + 90);
    triangle.setOutlineColor(sf::Color(0, 0, 0));
    triangle.setOutlineThickness(_height/15);
    win->draw(triangle);
}
