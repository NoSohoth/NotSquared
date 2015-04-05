#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Color.hpp"
#include "SFML/Graphics.hpp"

class Shape {
    protected:
        double _x;
        double _y;
        int _height;
        int _width;
        double _orientation;
        Color _color;

    public:
        Shape(double x, double y, int h, int w, double o, Color c):
            _x(x),
            _y(y),
            _height(h),
            _width(w),
            _orientation(o),
            _color(c) {}
        ~Shape(void) {}

        //Getters

        double getX() { return _x; }
        double getY() { return _y; }
        int getHeight() { return _height; }
        int getWidth() { return _width; }
        double getOrientation() { return _orientation; }

        //Setters

        void setX(double x) { _x=x; }
        void setY(double y) { _y=y; }
        void setOrientation(double o) { _orientation = o; }
        void setColor(Color c) { _color=c; }

        //Other methods

        virtual void draw(sf::RenderWindow *win) const = 0;
};

#endif
