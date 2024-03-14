#pragma once
#include "IMovable.h"
#include "IVisible.h"

class Entity : public IMovable, public IVisible
{
public:
    void teleportTunnels() override;
    Entity(float screenX_, float screenY_, float speed_, int tileX_, int tileY_, sf::Sprite* sprite_ = nullptr) :
            IMovable(screenX_, screenY_, speed_,tileX_, tileY_), IVisible(sprite_) {}
};
