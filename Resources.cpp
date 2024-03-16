#include "Resources.h"


std::map<int, sf::Sprite*> Resources::sprites;

sf::Texture Resources::Textures;
sf::Texture Resources::Labyrinth;

std::array<std::unique_ptr<sf::Sprite>,32> Resources::LabyrinthPieces;
std::vector<Resources::EntitySprite> Resources::vec_sprites;
const int Resources::PacMan = 0;
const int Resources::PacManDown = 1;
const int Resources::PacManLeft = 2;
const int Resources::PacManRight = 3;
const int Resources::Blinky = 4;
const int Resources::BlinkyDown = 5;
const int Resources::BlinkyLeft = 6;
const int Resources::BlinkyRight = 7;
const int Resources::Pinky = 8;
const int Resources::PinkyDown = 9;
const int Resources::PinkyLeft = 10;
const int Resources::PinkyRight = 11;
const int Resources::Inky = 12;
const int Resources::InkyDown = 13;
const int Resources::InkyLeft = 14;
const int Resources::InkyRight = 15;
const int Resources::Clyde = 16;
const int Resources::ClydeDown = 17;
const int Resources::ClydeLeft = 18;
const int Resources::ClydeRight = 19;
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
    for(int rect1 =0; rect1 < 4; ++rect1)
    {
        for (int rect2 = 0; rect2 < entity_number; ++rect2)
        {
            auto sprite = std::make_unique<sf::Sprite>(
                    sf::Sprite(Textures, sf::IntRect(rect1*45, rect2*15, 15, 15)));
            sprite->setScale(2.0f, 2.0f);
            sprite->setOrigin(7.5f, 7.5f);
            vec_sprites[rect1][dir[rect1]] = std::move(sprite);
        }
    }

    loadSprite(Resources::PacMan, 0, 0);
    loadSprite(Resources::PacManDown, 45, 0);
    loadSprite(Resources::PacManLeft, 90, 0);
    loadSprite(Resources::PacManRight, 135, 0);
    loadSprite(Resources::Blinky, 0, 15);
    loadSprite(Resources::BlinkyDown, 30, 15);
    loadSprite(Resources::BlinkyLeft, 60, 15);
    loadSprite(Resources::BlinkyRight, 90, 15);
    loadSprite(Resources::Pinky, 0, 30);
    loadSprite(Resources::PinkyDown, 30, 30);
    loadSprite(Resources::PinkyLeft, 60, 30);
    loadSprite(Resources::PinkyRight, 90, 30);
    loadSprite(Resources::Inky, 0, 45);
    loadSprite(Resources::InkyDown, 30, 45);
    loadSprite(Resources::InkyLeft, 60, 45);
    loadSprite(Resources::InkyRight, 90, 45);
    loadSprite(Resources::Clyde, 0, 60);
    loadSprite(Resources::ClydeDown, 30, 60);
    loadSprite(Resources::ClydeLeft, 60, 60);
    loadSprite(Resources::ClydeRight, 90, 60);
    loadSprite(Resources::FrightenedGhost, 120, 15);
    loadSprite(Resources::DeadPacMan, 0, 75);
}

sf::Sprite* Resources::get(int value, Direction facing)
{
    if (value != Resources::FrightenedGhost)
    {
        switch (facing)
        {
            case Direction::Down:
                value += 1;
                break;
            case Direction::Left:
                value += 2;
                break;
            case Direction::Right:
                value += 3;
                break;
//            case Direction::Unset:
//                facing = Direction::Up;
//                break;
        }

            //return vec_sprites[value / 4].at(facing).get();//(?)
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

