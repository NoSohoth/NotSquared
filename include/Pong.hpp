#ifndef PONG_HPP
#define PONG_HPP

#include <list>
#include "SFML/Graphics.hpp"
#include "Wall.hpp"
#include "Mobile.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"
#include "Texture.hpp"

class Pong {
	private:
		std::string _name;
    	int _width, _height;
		int _wallThickness, _movementSpeed;
		double _shootRate, _bulletHellRate;
		std::list<Wall> _walls;
		std::list<Mobile*> _mobiles;
    	sf::RenderWindow* _win;
	
	public:
		Pong(std::string n, int w, int h, int wT, int mS, double s,
				double bHR):
			_name(n),
			_width(w),
			_height(h),
			_wallThickness(wT),
			_movementSpeed(mS),
			_shootRate(s),
			_bulletHellRate(bHR),
			_win(new sf::RenderWindow(sf::VideoMode(_width, _height),
									  _name, sf::Style::Titlebar)) {}
		~Pong(void) { delete _win; }

		void addWall(Wall w);
		void addMobile(Mobile* m);
		void bulletHell();
		void collision();
		void createBorders();
		void drawAll();
		void hit();
		void handleEvents(bool&, bool&, bool&, bool&, bool&);
		void insertEnemies();
		void insertPlayer();
		void moveAll(double dt);
		void movePlayer(bool, bool, bool, bool);
		void popCircles();
		void shoot();

		void execute();
};

#endif
