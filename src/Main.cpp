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
	int fireRate = 333; //shoot every 'fireRate' frame
	int maxLifeTime = 7;
	Pong game("NotSquared", winW, winH, wallThickness, movementSpeed,
			  fireRate, maxLifeTime);
	
	// Run it !
	game.execute();
	return 0;
}
