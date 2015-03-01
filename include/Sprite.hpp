#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "SFML/Graphics.hpp"

class Sprite {
	private:
		sf::Texture _texture;
		double _x, _y, _scale;
		double _spriteXA, _spriteYA, _spriteXB, _spriteYB;

	public:
		Sprite(sf::Texture t,
				double x,
				double y,
				double s,
				double sXA=0.0,
				double sYA=0.0,
				double sXB=9999,
				double sYB=9999):
			_texture(t), _x(x), _y(y), _scale(s),
			_spriteXA(sXA), _spriteYA(sYA), _spriteXB(sXB), _spriteYB(sYB) {}
		~Sprite(void) {}

		void draw(sf::RenderWindow *win) const;
};

#endif
