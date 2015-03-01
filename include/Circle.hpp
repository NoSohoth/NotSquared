#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "SFML/Graphics.hpp"
#include "Mobile.hpp"

class Circle : public Mobile {
	public:
		Circle(double x, double y, int h, int w, double o, Color c, double d,
				int s, bool p):
			Mobile(x, y, h, w, o, c, d, s, p) {}
		~Circle(void) {}

		void move(double dt);
		void draw(sf::RenderWindow *win) const;
};

#endif
