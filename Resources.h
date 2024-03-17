#pragma once
#include "SFML/Graphics.hpp"
#include "Directions.h"
#include <map>
#include <array>
#include <memory>

class Resources {
private:
    static sf::Texture Textures;
    static sf::Texture Labyrinth;

    static void loadExtraSprite(int value, int rect1, int rect2);

    using EntitySprite = std::map<Direction, std::unique_ptr<sf::Sprite>>;
    static std::vector<EntitySprite> sprites;
    static std::map<int, std::unique_ptr<sf::Sprite>> extra_sprites;

public:
    static void load();

    static sf::Sprite *get(int value, Direction facing);

    static std::array<std::unique_ptr<sf::Sprite>, 32> LabyrinthPieces;

    static const int FrightenedGhost;
    static const int DeadPacMan;
};

