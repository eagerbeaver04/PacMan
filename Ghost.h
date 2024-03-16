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
    float calculateDistance(Labyrinth& labyrinth, int addX, int addY) const;
protected:
    void set_target(int x, int y) override;
    void movement() override;
    void teleport(int x, int y) override;
    void key(int code) override {};
    bool canMove(Labyrinth& labyrinth) override;
    void getSprite(int i) override;
    bool isOutHome() override;
    bool isScattering() override;
    void setFrightened(bool f) override;
    bool isFrightened() override;
public:
    Ghost(int tilePosX, int tilePosY, int destinationX, int destinationY, float speed);
    bool render(int& delay,const std::vector<Entity*>& entities, sf::RenderWindow* window, Labyrinth& labyrinth) override;
};