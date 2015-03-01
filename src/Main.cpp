#include <iostream>
#include <cmath>
#include "Pong.hpp"
#include "Triangle.hpp"
#include "Circle.hpp"

int main(void)
{
    srand(time(NULL));

	// Setting up game
	int winW = 1024;
	int winH = 768;
	int wallThickness = winH / 50;
	int movementSpeed = 500;
	double shootRate = 0.15; //shoot every 'fireRate' seconds
	double bulletHellRate = 0.5;
	
	Pong game("NotSquared", winW, winH, wallThickness, movementSpeed,
			  shootRate, bulletHellRate);
	
	// Run it !
	game.execute();
	return 0;
}
