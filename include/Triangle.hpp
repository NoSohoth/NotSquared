#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "SFML/Graphics.hpp"
#include "Mobile.hpp"

class Triangle : public Mobile {
	public:
		Triangle(double x, double y, int h, int w, double o, Color c, double d,
				int s, bool pB, int pL):
			Mobile(x, y, h, w, o, c, d, s, pB, pL) {}
		~Triangle(void) {}

		void move(double dt);
		void draw(sf::RenderWindow *win) const;
};

#endif
