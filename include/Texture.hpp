#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include "SFML/Graphics.hpp"

class Texture {
	private:
		sf::Texture _texture;
		double _x, _y;
		int _height, _width;
		std::string _path;

	public:
		Texture(double x, double y, int h, int w, std::string p):
				_x(x), _y(y), _height(h), _width(w), _path(p) {
			if (!_texture.loadFromFile(_path)) return;
		}
		~Texture(void) {}

		void draw(sf::RenderWindow *win) const;
};

#endif
