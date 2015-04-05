#ifndef WALL_HPP
#define WALL_HPP

#include "Shape.hpp"

class Wall : public Shape {
    private:
        double _coefficient;
    public:
        Wall(double x, double y, int h, int w, double o, Color c, double coeff):
            Shape(x, y, h, w, o, c), _coefficient(coeff) {}
        ~Wall(void) {}

        void draw(sf::RenderWindow *win) const;
};

#endif
