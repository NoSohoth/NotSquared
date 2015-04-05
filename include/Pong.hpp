#ifndef PONG_HPP
#define PONG_HPP

#include <list>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Wall.hpp"
#include "Mobile.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"
#include "Sprite.hpp"

class Pong {
    private:
        std::string _name;
        int _width, _height;
        int _wallThickness, _movementSpeed, _maxLife;
        double _shootRate, _bulletHellRate;
        bool _enableMusic;
        sf::RenderWindow* _win;
        std::list<Mobile*> _mobiles;
        std::vector<Sprite> _hearts;
        std::vector<Sprite> _stars;
        std::list<Wall> _walls;
    
    public:
        Pong(std::string n, int w, int h, int wT, int mS, int mL, double s,
                double bHR, bool eM):
            _name(n),
            _width(w),
            _height(h),
            _wallThickness(wT),
            _movementSpeed(mS),
            _maxLife(mL),
            _shootRate(s),
            _bulletHellRate(bHR),
            _enableMusic(eM),
            _win(new sf::RenderWindow(sf::VideoMode(_width, _height),
                                      _name, sf::Style::Titlebar)) {}
        ~Pong(void) { delete _win; }

        void addMobile(Mobile* m);
        void addHeart(Sprite s);
        void addStar(Sprite s);
        void addWall(Wall w);
        void bulletHell();
        void collision();
        void createBorders();
        void drawAll();
        void generateStars(sf::Texture, bool firstCall);
        bool hit(bool); // True if the player lost a life (to updateHearts())
        void handleEvents(bool&, bool&, bool&, bool&, bool&, bool&);
        void insertEnemies();
        void insertPlayer();
        void moveAll(double dt);
        void movePlayer(bool, bool, bool, bool);
        void removeCircles();
        void removeStars();
        void shoot();
        void updateHearts(sf::Texture);

        void execute();
};

#endif
