#ifndef MOBILE_HPP
#define MOBILE_HPP

#include "Shape.hpp"

class Mobile : public Shape {
	protected:
		double _direction;
		int _speed;
		double _lifeTime;
		bool _playersBullet;

	public:
		Mobile(double x, double y, int h, int w, double o, Color c, double d,
				int s, double lT, bool p):
			Shape(x, y, h, w, o, c),
			_direction(d),
			_speed(s),
			_lifeTime(lT),
			_playersBullet(p) {}
		virtual ~Mobile(void) {}

		virtual void move(double dt) = 0;
		virtual void draw(sf::RenderWindow *win) const = 0;

		double getDirection() { return _direction; }
		double getLifeTime() { return _lifeTime; }
		bool getPlayersBullet() { return _playersBullet; }

		void setDirection(double d) { _direction=d; }
		void setLifeTime(double lT) { _lifeTime=lT; }
		void setSpeed(int s) { _speed=s; }
};

#endif
