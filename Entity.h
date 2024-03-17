#pragma once

#include "IMovable.h"
#include "IVisible.h"

class Entity : public IMovable, public IVisible {
protected:
    void teleportTunnels() override;

public:
    Entity(float screenX_, float screenY_, float speed_, int tileX_, int tileY_, sf::Sprite *sprite_ = nullptr) :
            IMovable(screenX_, screenY_, speed_, tileX_, tileY_), IVisible(sprite_) {}

    void draw(sf::RenderWindow *window, Labyrinth &labyrinth) override;

    virtual ~Entity() = default;
};
