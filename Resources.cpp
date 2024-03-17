#include "Resources.h"

#include <memory>

sf::Texture Resources::Textures;
sf::Texture Resources::Labyrinth;

std::array<std::unique_ptr<sf::Sprite>, 32> Resources::LabyrinthPieces;
std::vector<Resources::EntitySprite> Resources::sprites;
std::map<int, std::unique_ptr<sf::Sprite>>  Resources::extra_sprites;
const int Resources::FrightenedGhost = 20;
const int Resources::DeadPacMan = 21;

void Resources::load() {
    Labyrinth.loadFromFile("textures/labyrinth.png");

    int index = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            LabyrinthPieces[index] = std::make_unique<sf::Sprite>(Labyrinth, sf::IntRect(i * 8, j * 8, 8, 8));
            LabyrinthPieces[index]->setScale(2.0f, 2.0f);
            index++;
        }
    }

    Textures.loadFromFile("textures/things.png");
    std::array<Direction, 4> dir = {Direction::Up, Direction::Down, Direction::Left, Direction::Right};
    int entity_number = 5;
    sprites.resize(5);
    int rect1Left = 45;
    int alpha = 15;
    for (int rect1 = 0; rect1 < entity_number; ++rect1) {
        for (int rect2 = 0; rect2 < 4; ++rect2) {
            auto sprite = std::make_unique<sf::Sprite>(
                    sf::Sprite(Textures, sf::IntRect(alpha + rect2 * rect1Left, rect1 * 15, 15, 15)));
            sprite->setScale(2.0f, 2.0f);
            sprite->setOrigin(7.5f, 7.5f);
            sprites[rect1][dir[rect2]] = std::move(sprite);
        }
        alpha = 0;
        rect1Left = 30;
    }

    loadExtraSprite(Resources::FrightenedGhost, 120, 15);
    loadExtraSprite(Resources::DeadPacMan, 0, 75);
}

sf::Sprite *Resources::get(int value, Direction facing)
{
    if (value != Resources::FrightenedGhost && value != Resources::DeadPacMan) {

        if (facing == Direction::Unset)
            facing = Direction::Up;

        return sprites[value / 4][facing].get();

    }

    return extra_sprites.at(value).get();

}


void Resources::loadExtraSprite(int value, int rect1, int rect2) {
    auto rect = std::make_unique<sf::IntRect>(rect1, rect2, 15, 15);
    auto sprite = std::make_unique<sf::Sprite>(Textures, *rect);
    sprite->setScale(2.0f, 2.0f);
    sprite->setOrigin(7.5f, 7.5f);
    extra_sprites.insert({value, std::move(sprite)});
}

