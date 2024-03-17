#pragma once

#include "Labyrinth.h"
#include "Resources.h"

class IVisible {
protected:
    sf::Sprite *sprite;

    virtual void getSprite(int i) = 0;

    explicit IVisible(sf::Sprite *sprite_ = nullptr) : sprite(sprite_) {}

    virtual void draw(sf::RenderWindow *window, Labyrinth &labyrinth) = 0;

    virtual ~IVisible() = default;
};


