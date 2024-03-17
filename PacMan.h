#pragma once

#include <queue>
#include <functional>

#include "Entity.h"


class PacMan : public Entity {
private:
    std::queue<Direction> directions;
    int eatenDots;
    bool dead;

    void stop();

    void queueDirection(Direction dir);

protected:
    void movement() override;

    void teleport(int x, int y) override;

    bool canMove(Labyrinth &labyrinth) override;

    void getSprite(int i) override;

public:
    PacMan();

    bool render(int &delay, const std::vector<std::unique_ptr<Entity>> &entities, sf::RenderWindow *window,
                Labyrinth &labyrinth) override;

    bool isScattering() override { return false; };

    bool isOutHome() override { return false; };

    void setFrightened(bool f) override {};

    void set_target(int x, int y) override {};

    bool isFrightened() override { return false; }

    void key(int code) override;
};
