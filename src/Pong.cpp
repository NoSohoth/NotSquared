#include <iostream>
#include <cmath>
#include <time.h>
#include "Pong.hpp"

using namespace std;


void Pong::addWall(Wall* w)
{
	_walls.push_back(w);
}


void Pong::addMobile(Mobile* m)
{
	_mobiles.push_back(m);
}


void Pong::collision()
{
	for (list<Mobile*>::iterator itM=_mobiles.begin();
		itM!=_mobiles.end(); itM++) {

		//Mobile modeling
		double infMobX = (*itM)->getX();
		double supMobX = infMobX + (*itM)->getWidth();
		double infMobY = (*itM)->getY();
		double supMobY = infMobY + (*itM)->getHeight();

		for (list<Wall*>::iterator itW=_walls.begin();
				itW!=_walls.end(); itW++) {

			//Wall modeling
	        double infWallX = (*itW)->getX();
        	double supWallX = infWallX + (*itW)->getWidth();
    	    double infWallY = (*itW)->getY();
	        double supWallY = infWallY + (*itW)->getHeight();

			//Ensure mobiles won't get out of the window (as a last resort !)
			if (infMobY<=0) {
				(*itM)->setY(infMobY + 2*_wallThickness);
			}
			else if (supMobY>=_height) {
				(*itM)->setY(infMobY - 2*_wallThickness);
			}

			//Is there a collision ?
			if ((infMobX>supWallX)
				|| (supMobX<infWallX)
				|| (infMobY>supWallY)
				|| (supMobY<infWallY)) {}

			else {
				double oldDir = (*itM)->getDirection();

				//  0° < oldDir < 90°
				if ( cos(oldDir)>0.0 && sin(oldDir)>=0.0 ) {
					//Bounce down
					if ( abs(supMobX-infWallX) > abs(infMobY-supWallY) ) {
						(*itM)->setDirection(- oldDir);	//newOri
						(*itM)->setY(infMobY + 2);	//Get away from the wall
					}
					//Bounce left
					else {
						(*itM)->setDirection(M_PI - oldDir);
						(*itM)->setX(infMobX - 2);
					}
				}
				else if ( cos(oldDir)>=0.0 && sin(oldDir)<0.0 ) {
					if ( abs(supMobX-infWallX) > abs(supMobY-infWallY) ) {
						(*itM)->setDirection(- oldDir);
						(*itM)->setY(infMobY - 2);
					}
					else {
						(*itM)->setDirection(M_PI - oldDir);
						(*itM)->setX(infMobX - 2);
					}
				}
				else if ( cos(oldDir)<=0.0 && sin(oldDir)>0.0 ) {
					if ( abs(infMobX-supWallX) > abs(infMobY-supWallY) ) {
						(*itM)->setDirection(- oldDir);
						(*itM)->setY(infMobY + 2);
					}
					else {
						(*itM)->setDirection(M_PI - oldDir);
						(*itM)->setX(infMobX + 2);
					}
				}
				else if ( cos(oldDir)<0.0 && sin(oldDir)<=0.0 ) {
					if ( abs(infMobX-supWallX) > abs(infWallY-supMobY) ) {
						(*itM)->setDirection(- oldDir);
						(*itM)->setY(infMobY - 2);
					}
					else {
						(*itM)->setDirection(M_PI - oldDir);
						(*itM)->setX(infMobX + 2);
					}
				}
				break;
			}
		}
	}
}


void Pong::createBorders()
{
	for (int i=0; i<8; i++)	{
		Color randomColor(rand()%256, rand()%256, rand()%256);
		addWall(new Wall((i/8.0) * _width, 0.0,				//Position
						 _wallThickness, _width/8,			//Size
						 0.0, randomColor, 0));				//Ori, color, coeff
		addWall(new Wall((i/8.0) * _width, _height - _wallThickness,
						 _wallThickness, _width/8,
						 0.0, randomColor, 0));
	}
/*	for (int i=0; i<5; i++)	{
		Color randomColor(rand()%256, rand()%256, rand()%256);
        addWall(new Wall(0.0, (i/5.0) * _height,
						 _height/5, _wallThickness,
						 0.0, randomColor, 0));
        addWall(new Wall(_width - _wallThickness, (i/5.0) * _height,
						 _height/5, _wallThickness,
						 0.0, randomColor, 0));
	}*/
}


void Pong::drawAll()
{
	for (list<Wall*>::iterator it=_walls.begin();
			it!=_walls.end(); it++) {
		(*it)->draw(_win);
	}
	for (list<Mobile*>::iterator it=_mobiles.begin();
			it!=_mobiles.end(); it++) {
       	(*it)->draw(_win);
	}
}


void Pong::handleEvents(bool& space,
						bool& up,
						bool& down,
						bool& left,
						bool& right)
{	
	sf::Event event;
	if (_win->pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed :
				_win->close();
				break;
			case sf::Event::KeyPressed :
				// Pause game
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					cout<< "Pause." <<endl;
					//pause();
				}

				// Start shooting
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					space = true;
				}

				// Player movements :
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) up=true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) down=true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) left=true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) right=true;
				break;
			case sf::Event::KeyReleased :
				if (event.key.code == sf::Keyboard::Up)	up=false;
				if (event.key.code == sf::Keyboard::Down) down=false;
				if (event.key.code == sf::Keyboard::Left) left=false;
				if (event.key.code == sf::Keyboard::Right) right=false;

				// Stop shooting
				if (event.key.code == sf::Keyboard::Space) {
					space = false;
				}
				break;
			default:
				break;
		}
	}
}


void Pong::insertEnnemies()
{
	//The ennemies are triangles contained in the _mobiles list
	for (int i=1; i<50; i++)
	{
		addMobile(new Triangle(rand()%5000 + _width,
			rand()%(5*_height/8) + _height/8, 100, 100, M_PI,
			Color(0,255,0), M_PI, 100, -1, false));
/*		addMobile(new Circle(3*winW/4, winH/2,
							 75, 75,
							 i*M_PI/25.0, red, 100));
*/	}
}


void Pong::insertPlayer()
{
	//The player is the first triangle in the _mobiles list
	addMobile(new Triangle(_width/5.0, _height/2.0, 40, 40, 0.0,
		Color(0,153,255), 0.0, 0, -1, false));
}


void Pong::moveAll(double dt)
{
	for (list<Mobile*>::iterator it=_mobiles.begin();
			it!=_mobiles.end(); it++) {
		(*it)->move(dt);
	}
}


void Pong::movePlayer(bool up, bool down, bool left, bool right)
{
	if (up == false && down == false && left == false && right == false) 
		_mobiles.front()->setSpeed(0);
	else {
		_mobiles.front()->setSpeed(_movementSpeed);
		if (up == true) {
			if (left == true) _mobiles.front()->setDirection(3*M_PI_4);
			else if (right == true) _mobiles.front()->setDirection(M_PI_4);
			else _mobiles.front()->setDirection(M_PI_2);
		}
		else if (down == true) {
			if (left == true) _mobiles.front()->setDirection(- 3*M_PI_4);
			else if (right == true) _mobiles.front()->setDirection(- M_PI_4);
			else _mobiles.front()->setDirection(- M_PI_2);
		}
		else if (left == true) _mobiles.front()->setDirection(M_PI);
		else if (right == true) _mobiles.front()->setDirection(0.0);
	}
}


void Pong::popCircles(double dt)
{
	for (list<Mobile*>::iterator it=_mobiles.begin();
			it!=_mobiles.end(); it++) {

		if (dynamic_cast<Circle*>(*it) != 0) {
			double lT = (*it)->getLifeTime();
			bool p = (*it)->getPlayersBullet();

			if (p == true) {
				double infX = (*it)->getX();
				double supX = infX + (*it)->getWidth();
				double infY = (*it)->getY();
				double supY = infY + (*it)->getHeight();
				if (infX>_width || supX<0.0 || infY>_height || supY<0.0) {
					it = _mobiles.erase(it);
				}
			}
			else if (lT > _maxLifeTime) it = _mobiles.erase(it);
			else (*it)->setLifeTime(lT + dt);
		}
	}
}


void Pong::shoot()
{
	addMobile(new Circle(_mobiles.front()->getX() + 7, // + circle height / 2
						 _mobiles.front()->getY() - 7, // - circle height / 2
						 14,
						 14,
						 0.0,
						 Color(255, 255, 255),
						 0.0,
						 1000,
						 5.0,
						 true));
}


void Pong::execute()
{
	sf::Clock clock;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool space = false;
	int shootFrameCounter = 0;

	_win->setKeyRepeatEnabled(false);
	createBorders();
	insertPlayer();
	insertEnnemies();

	while (_win->isOpen()) {
		// FPS
		sf::Time dt = clock.restart();
		cout << 1 / dt.asSeconds() << endl;

		// Check circles' lifeTime
		popCircles(dt.asSeconds());

		// Display
		_win->clear(sf::Color(128, 128, 128));
		collision();
		moveAll(dt.asSeconds());
		drawAll();
		_win->display();

		// Events
		handleEvents(space, up, down, left, right);
		movePlayer(up, down, left, right);

		// Shoot according to the _fireRate
		if (space) {	
			if (shootFrameCounter <= 0) {
				shoot();
				shootFrameCounter = _fireRate;
			}
			else shootFrameCounter--;
		}
		else shootFrameCounter = 0;
	}
}
