#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "SFML/Graphics.hpp"

class Sprite {
	private:
		sf::Texture _texture;
		double _x, _y, _scale, _direction, _speed;
		double _spriteXA, _spriteYA, _spriteXB, _spriteYB;

	public:
		Sprite(sf::Texture t,
				double x,
				double y,
				double sc,
				double d,
				double sp,
				double sXA,
				double sYA,
				double sXB,
				double sYB):
			_texture(t), _x(x), _y(y), _scale(sc), _direction(d), _speed(sp),
			_spriteXA(sXA), _spriteYA(sYA), _spriteXB(sXB), _spriteYB(sYB) {}
		~Sprite(void) {}

		double getX() { return _x; }
		double getScale() { return _scale; }
		double getSpriteXB() { return _spriteXB; }

		void move(double dt);
		void draw(sf::RenderWindow *win) const;
};

#endif
