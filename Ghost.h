#pragma once
#include "Entity.h"

class Ghost : public Entity
{
private:
    int targetX;
    int targetY;
    Direction moving;
    bool scattering;
    int frightened;
    bool outHome;
    bool decision;
public:
    Ghost(int tilePosX, int tilePosY, int destinationX, int destinationY, float speed);

    void set_target(int x, int y) override;
    void setDirection(Direction dir);
    Direction getDirection();

    void movement() override;
    void teleport(int x, int y) override;
    void key(int code) override {};
    bool canMove(Labyrinth& labyrinth) override;
    void draw(sf::RenderWindow* window, Labyrinth& labyrinth) override;
    void getSprite(int i) override;
    int getDots() override { return 0; };
    void setDead(bool d) override {};
    bool isDead() override { return false; };
    bool render(int& delay,const std::vector<Entity*>& entities, sf::RenderWindow* window, Labyrinth& labyrinth) override;
    bool isOutHome() override;

    bool isDecision() const;
    void setDecision(bool d);

    bool isScattering() override;
    void setScattering(bool s) override;

    void setFrightened(bool f) override;
    bool isFrightened() override;

    float calculateDistance(Labyrinth& labyrinth, int addX, int addY) const;
};