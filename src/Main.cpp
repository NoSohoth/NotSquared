#include <iostream>
#include <cmath>
#include "Pong.hpp"
#include "Triangle.hpp"
#include "Circle.hpp"

int main(void)
{
    srand(time(NULL));

	// Defining some basic colors
	Color red(255, 0, 0);
	Color green(0, 255, 0);
	Color blue(0, 0, 255);
	Color blue2(0, 153, 255);

	// Setting up game
	int winW = 1024;
	int winH = 768;
	int wallThickness = winH / 50;
	int movementSpeed = 500;
	int fireRate = 333; //shoot every 'fireRate' frame
	int maxLifeTime = 7;
	Pong game("NotSquared", winW, winH, wallThickness, movementSpeed,
			  fireRate, maxLifeTime);

	// Adding player
	
	game.addMobile(new Triangle(winW/5.0, winH/2.0, 40, 40,
		0.0, blue2, 0.0, 0, -1, false));

	// Adding ennemies
	for (int i=1; i<100; i++)
	{
		game.addMobile(new Triangle(rand()%10000 + winW,
			rand()%(5*winH/8) + winH/8, 100, 100, M_PI,
			green, M_PI, 100, -1, false));
/*		game.addMobile(new Circle(3*winW/4, winH/2,
								 75, 75,
								 i*M_PI/25.0, red, 100));
*/	}	

	// Run it !
	game.execute();
	return 0;
}
