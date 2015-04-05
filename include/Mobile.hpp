#ifndef MOBILE_HPP
#define MOBILE_HPP

#include "Shape.hpp"

class Mobile : public Shape {
    protected:
        double _direction;
        int _speed;
        bool _playersBullet;
        int _playersLives;

    public:
        Mobile(double x, double y, int h, int w, double o, Color c, double d,
                int s, bool pB, int pL):
            Shape(x, y, h, w, o, c),
            _direction(d),
            _speed(s),
            _playersBullet(pB),
            _playersLives(pL) {}
        virtual ~Mobile(void) {}

        virtual void move(double dt) = 0;
        virtual void draw(sf::RenderWindow *win) const = 0;

        double getDirection() { return _direction; }
        bool getPlayersBullet() { return _playersBullet; }
        int getPlayersLives() { return _playersLives; }

        void setDirection(double d) { _direction=d; }
        void setSpeed(int s) { _speed=s; }
        void setPlayersLives(int pL) { _playersLives=pL; }
};

#endif
