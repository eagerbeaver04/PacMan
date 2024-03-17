#pragma once

#include "SFML/Graphics.hpp"
#include "Directions.h"
#include <map>
#include <array>
#include <memory>
#include <iostream>

class Resources {
private:
    static sf::Texture Textures;
    static sf::Texture Labyrinth;

    static std::map<int, sf::Sprite *> sprites;

    static void loadSprite(int value, int rect1, int rect2);

    using EntitySprite = std::map<Direction, std::unique_ptr<sf::Sprite>>;
    static std::vector<EntitySprite> vec_sprites;

public:
    static void load();

    static sf::Sprite *get(int value, Direction facing);

    static std::array<std::unique_ptr<sf::Sprite>, 32> LabyrinthPieces;

    static const int PacMan;
    static const int Blinky;
    static const int Pinky;
    static const int Inky;
    static const int Clyde;
    static const int FrightenedGhost;
    static const int DeadPacMan;
};

