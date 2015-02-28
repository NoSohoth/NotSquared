#ifndef PONG_HPP
#define PONG_HPP

#include <list>
#include "SFML/Graphics.hpp"
#include "Wall.hpp"
#include "Mobile.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"

class Pong {
	private:
		std::string _name;
    	int _width, _height;
		int _wallThickness, _movementSpeed, _fireRate, _maxLifeTime;
		std::list<Wall*> _walls;
		std::list<Mobile*> _mobiles;
    	sf::RenderWindow* _win;
	
	public:
		Pong(std::string n, int w, int h, int wT, int mS, int f, int mLT):
			_name(n),
			_width(w),
			_height(h),
			_wallThickness(wT),
			_movementSpeed(mS),
			_fireRate(f),
			_maxLifeTime(mLT),
			_win(new sf::RenderWindow(sf::VideoMode(_width, _height),
									  _name, sf::Style::Titlebar)) {}
		~Pong(void) { delete _win; }

		void addWall(Wall* w);
		void addMobile(Mobile* m);
		void collision();
		void createBorders();
		void drawAll();
		void hit();
		void handleEvents(bool&, bool&, bool&, bool&, bool&);
		void insertEnemies();
		void insertPlayer();
		void moveAll(double dt);
		void movePlayer(bool, bool, bool, bool);
		void popCircles(double dt);
		void shoot();

		void execute();
};

#endif
