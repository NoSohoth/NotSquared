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
    int maxLife = 8; //Number of lives at the beginning
    double shootRate = 0.15; //shoot every 'fireRate' seconds
    double bulletHellRate = 0.3;
    bool enableMusic = true;
    
    Pong game("NotSquared", winW, winH, wallThickness, movementSpeed, maxLife,
              shootRate, bulletHellRate, enableMusic);
    
    // Run it !
    game.execute();
    return 0;
}
