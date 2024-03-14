#pragma once
#include <queue>
#include <functional>

#include "Entity.h"


class PacMan : public Entity
{
private:
    std::queue<Direction> directions;
    std::vector < std::function<void()>> fruiteatencallbacks;
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
    bool isFrightened() override;
    bool isScattering() override { return false; };
    void setScattering(bool s)override {};
    void draw(sf::RenderWindow* window, Labyrinth& labyrinth) override;
    void getSprite(int i) override;
    bool isOutHome() override { return false; };
    std::queue<Direction> getDirections();
    void stop();
    void eatDot();
    int getDots() override;
    void set_target(int x, int y) override {};
    void setDead(bool d) override;
    bool isDead() override;
    bool render(int& delay, const std::vector<Entity*>& entities, sf::RenderWindow* window, Labyrinth& labyrinth) override;
};
