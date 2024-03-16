#pragma once

#include "PacMan.h"
#include "Ghost.h"


#include <cmath>
#include <random>
#include <cstdlib>


class Scene
{
private:
    Labyrinth labyrinth;
    std::vector<std::unique_ptr<Entity>> entities;
    int delay;
    void draw(sf::RenderWindow* window);
public:
    void init();
    void loop(sf::RenderWindow* window);
    void create(sf::RenderWindow* window);
    void key(int code);
};