#include "Resources.h"


std::map<int, sf::Sprite*> Resources::sprites;

sf::Texture Resources::Textures;
sf::Texture Resources::Labyrinth;

std::array<std::unique_ptr<sf::Sprite>,32> Resources::LabyrinthPieces;
std::vector<Resources::EntitySprite> Resources::vec_sprites;
const int Resources::PacMan = 0;

const int Resources::Blinky = 4;

const int Resources::Pinky = 8;

const int Resources::Inky = 12;

const int Resources::Clyde = 16;

const int Resources::FrightenedGhost = 20;
const int Resources::DeadPacMan = 21;

void Resources::load()
{
    Labyrinth.loadFromFile("textures/labyrinth.png");

    int index = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            LabyrinthPieces[index] = std::make_unique<sf::Sprite>(Labyrinth, sf::IntRect(i * 8, j * 8, 8, 8));
            LabyrinthPieces[index]->setScale(2.0f, 2.0f);
            index++;
        }
    }

    Textures.loadFromFile("textures/things.png");
    std::array<Direction, 4> dir = {Direction::Up, Direction::Down, Direction::Left, Direction::Right};
    int entity_number = 5;
    vec_sprites.resize(5);
    int rect1Left = 45;
    int alpha = 15;
    for(int rect1 =0; rect1 < entity_number; ++rect1)
    {
        for (int rect2 = 0; rect2 < 4; ++rect2)
        {
            auto sprite = std::make_unique<sf::Sprite>(
                    sf::Sprite(Textures, sf::IntRect(alpha + rect2*rect1Left, rect1*15, 15, 15)));
            sprite->setScale(2.0f, 2.0f);
            sprite->setOrigin(7.5f, 7.5f);
            vec_sprites[rect1][dir[rect2]] = std::move(sprite);
        }
        alpha = 0;
        rect1Left = 30;
    }

    loadSprite(Resources::FrightenedGhost, 120, 15);
    loadSprite(Resources::DeadPacMan, 0, 75);
}

sf::Sprite* Resources::get(int value, Direction facing)
{
    if (value != Resources::FrightenedGhost && value != Resources::DeadPacMan)
    {

            if (facing == Direction::Unset)
                facing = Direction::Up;
            if(value == 0)
                std::cout <<"value = " << value << ", facing=" << static_cast<int>(facing) << std::endl;
            return vec_sprites[value / 4][facing].get();

    }

    return sprites.at(value);

}


void Resources::loadSprite(int value, int rect1, int rect2)
{
    sf::IntRect* rect = new sf::IntRect(rect1, rect2, 15, 15);
    sf::Sprite* sprite = new sf::Sprite(Textures, *rect);
    sprite->setScale(2.0f, 2.0f);
    sprite->setOrigin(7.5f, 7.5f);
    sprites.insert({value, sprite});
}

