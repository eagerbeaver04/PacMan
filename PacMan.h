#pragma once
#include <queue>
#include <functional>

#include "Entity.h"


class PacMan : public Entity
{
private:
    std::queue<Direction> directions;
    int eatenDots;
    bool dead;

public:
    PacMan();
    void movement() override;
    void teleport(int x, int y) override;
    void key(int code) override;
    void queueDirection(Direction dir);
    bool canMove(Labyrinth& labyrinth) override;
    void setFrightened(bool f) override {};
    bool isScattering() override { return false; };
    void setScattering(bool s)override {};
    void getSprite(int i) override;
    bool isOutHome() override { return false; };
    void stop();
    bool isFrightened() override { return false;}
    void set_target(int x, int y) override {};
    bool render(int& delay, const std::vector<Entity*>& entities, sf::RenderWindow* window, Labyrinth& labyrinth) override;
};
