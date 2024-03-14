
#include "PacMan.h"
using namespace  std;
using namespace sf;

PacMan::PacMan() : Entity(13 * 16.0f + 8.0f + 8.0f, 26 * 16.0f + 8.0f, 0.1f, 13, 26)
{
    dead = false;
    eatenDots = 0;
}

void PacMan::teleport(int x, int y)
{
    tileX = x;
    tileY = y;
    screenX = x * 16.0f + 8.0f;
    screenY = y * 16.0f + 8.0f;
}

void PacMan::queueDirection(Direction dir)
{
    if (!directions.empty())
    {
        if (static_cast<int>(dir) == -static_cast<int>(directions.front()))
        {
            std::queue<Direction> clear;
            std::swap(directions, clear);
        }
    }

    if (directions.size() < 2)
        directions.push(dir);
}

void PacMan::key(int code)
{
    switch (code)
    {
        case Keyboard::Up:
            this->queueDirection(Direction::Up);
            break;
        case Keyboard::Down:
            this->queueDirection(Direction::Down);
            break;
        case Keyboard::Left:
            this->queueDirection(Direction::Left);
            break;
        case Keyboard::Right:
            this->queueDirection(Direction::Right);
            break;
    }
}

void PacMan::movement()
{
    if (!directions.empty())
    {
        switch (directions.front())
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
        }
    }
}

bool PacMan::canMove(Labyrinth& labyrinth)
{
    if (!this->getDirections().empty())
    {
        switch (this->getDirections().front())
        {
            case Direction::Up:
                return !labyrinth.tileEntity(this->getTileX(), this->getTileY() - 1);
                break;
            case Direction::Down:
                return !labyrinth.tileEntity(this->getTileX(), this->getTileY() + 1);
                break;
            case Direction::Left:
                return !labyrinth.tileEntity(this->getTileX() - 1, this->getTileY());
                break;
            case Direction::Right:
                return !labyrinth.tileEntity(this->getTileX() + 1, this->getTileY());
                break;
        }
    }
    return true;
}

queue<Direction> PacMan::getDirections()
{
    return directions;
}

void PacMan::stop()
{
    if (directions.size() > 1)
    {
        if ((int)(screenX + 8) % 16 == 0 && (int)(screenY + 8) % 16 == 0)
        {
            switch (directions.front())
            {
                case Direction::Up:
                    directions.pop();
                    break;
                case Direction::Down:
                    directions.pop();
                    break;
                case Direction::Left:
                    directions.pop();
                    break;
                case Direction::Right:
                    directions.pop();
                    break;
            }
        }
    }
}

void PacMan::eatDot()
{
    eatenDots++;
}

int PacMan::getDots()
{
    return eatenDots;
}

void PacMan::setDead(bool d)
{
    dead = d;
}

bool PacMan::isDead()
{
    return dead;
}

bool PacMan::isFrightened()
{
    return false;
}

void PacMan::getSprite(int i)
{
    if (this->getDirections().empty())
        sprite = Resources::get(Resources::PacMan, Direction::Unset);
    else
        sprite = Resources::get(Resources::PacMan, this->getDirections().front());
    if (this->isDead())
        sprite = Resources::get(Resources::DeadPacMan, Direction::Unset);
}

void PacMan::draw(RenderWindow* window, Labyrinth& labyrinth)
{
    this->getSprite(0);
    sprite->setPosition(this->getScreenX(), this->getScreenY());
    window->draw(*sprite);
}

bool PacMan::render(int& delay,const vector<Entity*>& entities, RenderWindow* window, Labyrinth& labyrinth)
{
    this->teleportTunnels();

    if (canMove(labyrinth) && !this->isDead())
        this->movement();

    if (labyrinth.isIntersection(this->getTileX(), this->getTileY()))
        this->stop();

    if (labyrinth.getValue(this->getTileX(), this->getTileY()) == 26)
    {
        labyrinth.setValue(this->getTileX(), this->getTileY(), 30);
        this->eatDot();
    }

    else if (labyrinth.getValue(this->getTileX(), this->getTileY()) == 27)
    {
        labyrinth.setValue(this->getTileX(), this->getTileY(), 30);
        {
            for (Entity* entity : entities)
                if (entity != this)
                    entity->setFrightened(true);
        }
    }

    if (this->getDots() == 240)
    {
        for (Entity* ghost : entities)
        {
            if (ghost != this)
                ghost->teleport(-2, -2);
        }
        delay++;
    }
    if (this->isDead())
        delay++;

    if (delay == 200)
    {
        if (this->isDead())
        {
            for (Entity* ghost : entities)
            {
                if (ghost != this)
                {
                    if(ghost->isOutHome())
                        ghost->teleport(13, 14);
                }
            }
            this->teleport(13, 26);
            this->setDead(false);
            delay = 0;
        }
        else return false;
    }

    if (this->eatenDots == 5)
    {
        for (Entity* ghost : entities)
        {
            if (ghost != this && !ghost->isOutHome())
            {
                ghost->teleport(13, 14);
                break;
            }
        }
    }

    if (this->eatenDots == 50)
    {
        for (Entity* ghost : entities)
        {
            if (ghost != this && !(ghost->isOutHome()))
            {
                ghost->teleport(13, 14);
                break;
            }
        }
    }

    for (Entity* ghost : entities)
    {
        if (ghost != this)
        {
            if (!ghost->isScattering())
                ghost->set_target(this->getTileX(), this->getTileY());

            if (this->getTileX() == ghost->getTileX() && this->getTileY() == ghost->getTileY())
            {

                if (ghost->isFrightened())
                {
                    ghost->teleport(13, 14);
                    ghost->setFrightened(false);
                }
                else
                {
                    this->setDead(true);
                    directions = {};
                    for(Entity* ghost1 : entities)
                        ghost1->teleport(-2, -2);
                }
            }

        }
    }
    return true;
}