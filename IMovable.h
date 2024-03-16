#pragma once
#include <cmath>
#include "Labyrinth.h"
#include "Resources.h"
class Entity;

class IMovable
{
protected:
    float screenX;
    float screenY;
    float speed;
    int tileX;
    int tileY;
    virtual void move(float x, float y);
    virtual void movement() = 0;
    virtual bool canMove(Labyrinth& labyrinth) = 0;
    virtual void teleportTunnels() = 0;
    IMovable(float screenX_, float screenY_, float speed_, int tileX_, int tileY_):
            screenX(screenX_), screenY(screenY_), speed(speed_), tileX(tileX_), tileY(tileY_){}
public:
    [[nodiscard]] int getTileX() const { return tileX; }
    [[nodiscard]] int getTileY() const { return tileY; }
    virtual bool isScattering() = 0;
    virtual bool render(int& delay,const std::vector<Entity*>& entities, sf::RenderWindow* window, Labyrinth& labyrinth) = 0;
    virtual void teleport(int x, int y) = 0;
    virtual bool isOutHome() = 0;
    virtual void setFrightened(bool f) =0;
    virtual void set_target(int x, int y) = 0;
    virtual bool isFrightened() = 0;
    virtual void key(int code) = 0;
    virtual ~IMovable() = default;
};