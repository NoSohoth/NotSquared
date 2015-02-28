#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "SFML/Graphics.hpp"
//#include "Color.h"
#include "Mobile.hpp"

class Triangle : public Mobile {
	public:
		Triangle(double x, double y, int h, int w, double o, Color c, double d,
				int s, double lT, bool p):
			Mobile(x, y, h, w, o, c, d, s, lT, p) {}
		~Triangle(void) {}

		void move(double dt);
		void draw(sf::RenderWindow *win) const;
};

#endif
