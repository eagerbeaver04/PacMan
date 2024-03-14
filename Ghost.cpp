#include "Ghost.h"


Ghost::Ghost(int tilePosX_, int tilePosY_, int targetX_, int targetY_, float speed_)
: Entity(tilePosX_ * 16.0f + 8.0f + 8.0f, tilePosY_ * 16.0f + 8.0f, speed_, tilePosX_, tilePosY_)
{

    targetX = targetX_;
    targetY = targetY_;
    moving = Direction::Unset;
    scattering = true;
    outHome = false;
    decision = true;
    frightened = false;
}

void Ghost::set_target(int x, int y)
{
    targetX = x;
    targetY = y;
}

void Ghost::setDirection(Direction dir)
{
    moving = dir;
}

Direction Ghost::getDirection()
{
    return moving;
}

void Ghost::movement()
{
    switch (moving)
    {
        case Direction::Up:
            move(0, -speed);
            break;
        case Direction::Down:
            move(0, speed);
            break;
        case Direction::Left:
            move(-speed, 0);
            break;
        case Direction::Right:
            move(speed, 0);
            break;
        case Direction::Unset:
            break;
    }
}

bool Ghost::isScattering()
{
    return scattering;
}

void Ghost::setScattering(bool s)
{
    scattering = s;
}

bool Ghost::isOutHome()
{
    return outHome;
}

bool Ghost::isDecision() const
{
    return decision;
}

void Ghost::setDecision(bool d)
{
    decision = d;
}

void Ghost::teleport(int x, int y)
{
    tileX = x;
    tileY = y;
    screenX = x * 16.0f + 8.0f;
    screenY = y * 16.0f + 8.0f;
    outHome = true;
}

void Ghost::setFrightened(bool f)
{
    if (f)
        frightened = 2000;
    else
        frightened = 0;
}

bool Ghost::isFrightened()
{
    if (frightened > 0) frightened--;
    return frightened > 0;
}


bool Ghost::canMove(Labyrinth& labyrinth)
{
    switch (this->getDirection())
    {
        case Direction::Up:
            return !labyrinth.tileEntity(tileX, tileY - 1);
            break;
        case Direction::Down:
            return !labyrinth.tileEntity(tileX, tileY + 1);
            break;
        case Direction::Left:
            return !labyrinth.tileEntity(tileX - 1, tileY);
            break;
        case Direction::Right:
            return !labyrinth.tileEntity(tileX + 1, tileY);
            break;
        default:
            return false;
    }
}

void Ghost::getSprite(int i)
{
    if (!this->isFrightened())
        sprite = Resources::get(Resources::Pinky, this->getDirection());
    else
        sprite = Resources::get(Resources::FrightenedGhost, this->getDirection());
}

float Ghost::calculateDistance(Labyrinth& labyrinth, int addX, int addY) const
{
    float distance = 1000000.0f;
    if (!labyrinth.tileEntity(targetX + addX, targetY + addY))
        distance = (float)sqrt(pow((targetX - (targetX + addX)), 2) + pow((targetY - (targetY+ addY)), 2));
    return distance;
}

void Ghost::draw(sf::RenderWindow* window, Labyrinth& labyrinth)
{
    this->getSprite();
    sprite->setPosition(screenX, screenY);
    window->draw(*sprite);
}

bool Ghost::render(int& delay,const std::vector<Entity*>& entities, sf::RenderWindow* window, Labyrinth& labyrinth)
{
    if (this->isScattering())
    {
        if (tileX == targetX && tileY == targetY)
            this->setScattering(false);
    }

    if (labyrinth.isIntersection(tileX, tileY))
    {
        if (this->isDecision())
        {
            float dRight = calculateDistance(labyrinth, 1, 0);
            float dLeft = calculateDistance(labyrinth, -1, 0);
            float dUp = calculateDistance(labyrinth, 0, -1);
            float dDown = calculateDistance(labyrinth, 0, 1);

            if (dRight < dLeft && dRight < dUp && dRight < dDown)
                this->setDirection(Direction::Right);
            else if (dLeft < dRight && dLeft < dUp && dLeft < dDown)
                this->setDirection(Direction::Left);
            else if (dUp < dLeft && dUp < dRight && dUp < dDown)
                this->setDirection(Direction::Up);
            else if (dDown < dLeft && dDown < dUp && dDown < dRight)
                this->setDirection(Direction::Down);
        }
        this->setDecision(false);
    }
    else
        this->setDecision(true);

    if (this->canMove(labyrinth) && this->isOutHome())
        this->movement();
    else
        this->setDecision(true);

    return true;
}