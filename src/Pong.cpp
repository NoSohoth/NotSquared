#include <iostream>
#include <cmath>
#include <time.h>
#include "Pong.hpp"

using namespace std;


void Pong::addMobile(Mobile* m)
{
	_mobiles.push_back(m);
}


void Pong::addHeart(Sprite s)
{
	_hearts.push_back(s);
}


void Pong::addStar(Sprite s)
{
	_stars.push_back(s);
}


void Pong::addWall(Wall w)
{
	_walls.push_back(w);
}


void Pong::bulletHell()
{
	for (list<Mobile*>::iterator enemy=_mobiles.begin();
			enemy!=_mobiles.end(); enemy++) {
		if (dynamic_cast<Triangle*>(*enemy) != 0 && enemy != _mobiles.begin()) {
			for (int i=-1; i<2; i++) {
				addMobile(new Circle((*enemy)->getX(), (*enemy)->getY() - 5,
					10, 10, 0.0, _MAROON, M_PI + i*M_PI/9.0, 250, false, -1));
			}	
		}
	}
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

		for (list<Wall>::iterator itW=_walls.begin();
				itW!=_walls.end(); itW++) {

			//Wall modeling
	        double infWallX = itW->getX();
        	double supWallX = infWallX + itW->getWidth();
			double infWallY = itW->getY();
	        double supWallY = infWallY + itW->getHeight();

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
		addWall(Wall((i/8.0) * _width, 0.0,				//Position
					 _wallThickness, _width/8,			//Size
					 0.0, randomColor, 0));				//Ori, color, coeff
		addWall(Wall((i/8.0) * _width, _height - _wallThickness,
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
	for (vector<Sprite>::iterator it=_stars.begin();
			it!=_stars.end(); it++) {
		it->draw(_win);
	}
	for (list<Wall>::iterator it=_walls.begin();
			it!=_walls.end(); it++) {
		it->draw(_win);
	}
	for (list<Mobile*>::reverse_iterator it=_mobiles.rbegin();
			it!=_mobiles.rend(); it++) {
       	(*it)->draw(_win);
	}
	for (vector<Sprite>::iterator it=_hearts.begin();
			it!=_hearts.end(); it++) {
		it->draw(_win);
	}

}


void Pong::generateStars(sf::Texture tStar, bool firstCall)
{
	if (!firstCall) {
	addStar(Sprite(tStar, _width, rand()%((int) _height),
			(rand()%8)/100.0, M_PI, 40, 0.0, 0.0, 200.0, 200.0));
	}
	else {
		for (int i=0; i<150; i++) {
			addStar(Sprite(tStar, rand()%((int) _width), rand()%((int) _height),
					(rand()%8)/100.0, M_PI, 40, 0.0, 0.0, 200.0, 200.0));
		}
	}
}


void Pong::handleEvents(bool& space, bool& up, bool& down, bool& left,
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

bool Pong::hit(bool playerIsInvulnerable)
{
	// For each bullet
	for (list<Mobile*>::iterator bullet=_mobiles.begin();
			bullet!=_mobiles.end(); bullet++) {
		if (dynamic_cast<Circle*>(*bullet) != 0) {

			// Bullet center coordinates
			double bRadius = (*bullet)->getWidth()/2;
			double bX = (*bullet)->getX() + bRadius;
			double bY = (*bullet)->getY() + bRadius;

			// For each characters (player and enemies)
			for (list<Mobile*>::iterator ch=_mobiles.begin();
					ch!=_mobiles.end(); ch++) {
				if (dynamic_cast<Triangle*>(*ch) != 0) {

					// Character's center coordinates
					double cX = (*ch)->getX();
					double cY = (*ch)->getY();
					// Distance between the two
					double distance = sqrt( pow(cX-bX,2) + pow(cY-bY,2)  );
					// The hitbox is a circle
					double hitboxRadius = (*ch)->getWidth()/2;

					// Did the player get hit ?
					if (ch == _mobiles.begin()
							&& (*bullet)->getPlayersBullet() == false
							&& distance < hitboxRadius/3.0 + bRadius
							&& playerIsInvulnerable == false) {
						int currentLives = (*ch)->getPlayersLives() - 1;
						if (currentLives == 0) _win->close();
						else (*ch)->setPlayersLives(currentLives);
						bullet = _mobiles.erase(bullet);
						return true;
					}
					// Or maybe an enemy got hit by a player's bullet ?
					else if (ch != _mobiles.begin()
							&& (*bullet)->getPlayersBullet() == true
							&& distance < hitboxRadius + bRadius) {
						ch = _mobiles.erase(ch);
						bullet = _mobiles.erase(bullet);
						return false;
					}
				}
			}
		}
	}
	return false;
}


void Pong::insertEnemies()
{
	//The enemies are triangles contained in the _mobiles list
	for (int i=1; i<30; i++)
	{
		addMobile(new Triangle(rand()%5000 + _width,
			rand()%(5*_height/8) + _height/8, 50, 50, M_PI,
			_GREEN, M_PI, 150, false, -1));
/*		addMobile(new Circle(3*winW/4, winH/2,
							 75, 75,
							 i*M_PI/25.0, red, 100));
*/	}
}


void Pong::insertPlayer()
{
	//The player is the first triangle in the _mobiles list
	addMobile(new Triangle(_width/5.0, _height/2.0, 40, 40, 0.0,
		_CRIMSON, 0.0, 0, false, _maxLife));
}


void Pong::moveAll(double dt)
{
	for (list<Mobile*>::iterator it=_mobiles.begin();
			it!=_mobiles.end(); it++) {
		(*it)->move(dt);
	}
	for (vector<Sprite>::iterator it=_stars.begin();
			it!=_stars.end(); it++) {
		it->move(dt);
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


void Pong::removeCircles()
{
	// Remove bullets when they're out of the window
	for (list<Mobile*>::iterator it=_mobiles.begin();
			it!=_mobiles.end(); it++) {

		if (dynamic_cast<Circle*>(*it) != 0) {
			double infX = (*it)->getX();
			double supX = infX + (*it)->getWidth();
			double infY = (*it)->getY();
			double supY = infY + (*it)->getHeight();
			if (infX>_width || supX<0.0 || infY>_height || supY<0.0) {
				it = _mobiles.erase(it);
			}
		}
	}
}


void Pong::removeStars()
{
	for (vector<Sprite>::iterator it=_stars.begin();
			it!=_stars.end(); it++) {
		if (it->getX() + (it->getSpriteXB() * it->getScale()) < 0.0) {
			it = _stars.erase(it);
		}
	}
}


void Pong::shoot()
{
	addMobile(new Circle(_mobiles.front()->getX() + 7, // + circle height / 2
						 _mobiles.front()->getY() - 7, // - circle height / 2
						 14, 14, 0.0, _BLUE, 0.0, 1000, true, -1));
}


void Pong::updateHearts(sf::Texture tHeart)
{
	int lives = _mobiles.front()->getPlayersLives();
	_hearts.clear();

	for (int i=0; i<lives; i++) {
		addHeart(Sprite(tHeart, 20.0 + i*50.0, 20.0, 0.2, 0.0, 0.0,
				0.0, 0.0, 212.0, 201.0));
	}
	for (int i=lives; i<_maxLife; i++) {
		addHeart(Sprite(tHeart, 20.0 + i*50.0, 20.0, 0.2, 0.0, 0.0,
				212.0, 0.0, 424.0, 201.0));
	}
}


void Pong::execute()
{
	sf::Clock clock;
	sf::Music music;
	sf::Texture tHeart;
	sf::Texture tStar;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool space = false;
	bool playerIsInvulnerable = false;
	double shootTimer = 0.0;
	double bulletHellTimer = 0.0;
	double starsTimer = 0.0;
	double hitTimer = 0.0;

	// Load textures & sounds
	if (!tHeart.loadFromFile("textures/heart.png")) return;
	if (!tStar.loadFromFile("textures/star.png")) return;
	if (_enableMusic) {
		if (!music.openFromFile("sounds/background.ogg")) return;
	}

	// Load game
	_win->setKeyRepeatEnabled(false);
	if (_enableMusic) music.play();
	generateStars(tStar, true);
	createBorders();
	insertPlayer();
	insertEnemies();
	updateHearts(tHeart);

	while (_win->isOpen()) {
		//------------------//
		// FPS & delta time //
		//------------------//
		sf::Time dt = clock.restart();
		cout << 1 / dt.asSeconds() << endl;


		//--------//
		// Inputs //
		//--------//
		handleEvents(space, up, down, left, right);
		movePlayer(up, down, left, right);


		//-----------------//
		// Bullet handling //
		//-----------------//
			// Player
		if (space) {	
			if (shootTimer <= 0.0) {
				shoot();
				shootTimer = _shootRate;
			} else shootTimer -= dt.asSeconds();
		} else shootTimer = 0;
			// Enemies
		if (bulletHellTimer <= 0.0) {
			bulletHell();
			bulletHellTimer = _bulletHellRate;
		} else bulletHellTimer -= dt.asSeconds();


		//----------------//
		// Event handling //
		//----------------//
			// Remove out-of-screen bullets and stars
		removeCircles();
		removeStars();
			// Handle hit characters
		bool playerHit = hit(playerIsInvulnerable);	// Did anyone hit anyone ?
		if (playerHit) {
			updateHearts(tHeart);		// If so, update displayed life count
			playerIsInvulnerable = true;
			hitTimer = 2.0;				//Then start a timer
		}
			// To make the player blink so that he can see that he got hit
		if (hitTimer != 0.0) {
			if (((int) (hitTimer*20.0))%2 == 0) {
				_mobiles.front()->setColor(_BLACK);
			}
			else _mobiles.front()->setColor(_CRIMSON);
			hitTimer -= dt.asSeconds();
			if (hitTimer < 0.0) {
				hitTimer = 0.0;
				_mobiles.front()->setColor(_CRIMSON);
				playerIsInvulnerable = false;
			}
		}
			// Collisions between mobiles and walls
		collision();


		//---------------------------------//
		// Update position of every entity //
		//---------------------------------//
		moveAll(dt.asSeconds());


		//---------//
		// Display //
		//---------//
			// Clear screen
		_win->clear(sf::Color(0, 0, 0));
			// Build the background with stars using stripes
		if (starsTimer <= 0.0) {
			generateStars(tStar, false);
			starsTimer = 0.4;
		} else starsTimer -= dt.asSeconds();
			// Draw every entity in SFML
		drawAll();
			// Display them
		_win->display();
	}
}
