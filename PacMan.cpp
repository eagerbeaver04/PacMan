
#include "PacMan.h"

PacMan::PacMan() : Entity(13 * 16.0f + 8.0f + 8.0f, 26 * 16.0f + 8.0f, 0.1f, 13, 26) {
    dead = false;
    eatenDots = 0;
}

void PacMan::teleport(int x, int y) {
    tileX = x;
    tileY = y;
    screenX = x * 16.0f + 8.0f;
    screenY = y * 16.0f + 8.0f;
}

void PacMan::queueDirection(Direction dir) {
    if (!directions.empty()) {
        if (static_cast<int>(dir) == -static_cast<int>(directions.front())) {
            std::queue<Direction> clear;
            std::swap(directions, clear);
        }
    }

    if (directions.size() < 2)
        directions.push(dir);
}

void PacMan::key(int code) {
    switch (code) {
        case sf::Keyboard::Up:
            queueDirection(Direction::Up);
            return;
        case sf::Keyboard::Down:
            queueDirection(Direction::Down);
            return;
        case sf::Keyboard::Left:
            queueDirection(Direction::Left);
            return;
        case sf::Keyboard::Right:
            queueDirection(Direction::Right);
            return;
    }
}

void PacMan::movement() {
    if (!directions.empty()) {
        switch (directions.front()) {
            case Direction::Up:
                move(0, -speed);
                return;
            case Direction::Down:
                move(0, speed);
                return;
            case Direction::Left:
                move(-speed, 0);
                return;
            case Direction::Right:
                move(speed, 0);
                return;
        }
    }
}

bool PacMan::canMove(Labyrinth &labyrinth) {
    if (!directions.empty()) {
        switch (directions.front()) {
            case Direction::Up:
                return !labyrinth.tileEntity(tileX, tileY - 1);

            case Direction::Down:
                return !labyrinth.tileEntity(tileX, tileY + 1);

            case Direction::Left:
                return !labyrinth.tileEntity(tileX - 1, tileY);

            case Direction::Right:
                return !labyrinth.tileEntity(tileX + 1, tileY);

        }
    }
    return true;
}

void PacMan::stop() {
    if (directions.size() > 1) {
        if (static_cast<int>(screenX + 8) % 16 == 0 && static_cast<int>(screenY + 8) % 16 == 0) {
            switch (directions.front()) {
                case Direction::Up:
                    directions.pop();
                    return;
                case Direction::Down:
                    directions.pop();
                    return;
                case Direction::Left:
                    directions.pop();
                    return;
                case Direction::Right:
                    directions.pop();
                    return;
            }
        }
    }
}

void PacMan::getSprite(int i) {
    if (directions.empty())
        sprite = Resources::get(Resources::PacMan, Direction::Unset);
    else
        sprite = Resources::get(Resources::PacMan, directions.front());
    if (dead)
        sprite = Resources::get(Resources::DeadPacMan, Direction::Unset);
}


bool PacMan::render(int &delay, const std::vector<std::unique_ptr<Entity>> &entities, sf::RenderWindow *window,
                    Labyrinth &labyrinth) {
    teleportTunnels();

    if (canMove(labyrinth) && !dead)
        movement();

    if (labyrinth.isIntersection(tileX, tileY))
        stop();

    if (labyrinth.getValue(tileX, tileY) == 26) {
        labyrinth.setValue(tileX, tileY, 30);
        eatenDots++;
    } else if (labyrinth.getValue(tileX, tileY) == 27) {
        labyrinth.setValue(tileX, tileY, 30);
        {
            for (auto &&entity: entities)
                if (entity.get() != this)
                    entity->setFrightened(true);
        }
    }

    if (eatenDots == 240) {
        for (auto &&ghost: entities) {
            if (ghost.get() != this)
                ghost->teleport(-2, -2);
        }
        delay++;
    }
    if (dead)
        delay++;

    if (delay == 200) {
        if (dead) {
            for (auto &&ghost: entities) {
                if (ghost.get() != this) {
                    if (ghost->isOutHome())
                        ghost->teleport(13, 14);
                }
            }
            teleport(13, 26);
            dead = false;
            delay = 0;
        } else return false;
    }

    if (eatenDots == 5) {
        for (auto &&ghost: entities) {
            if (ghost.get() != this && !ghost->isOutHome()) {
                ghost->teleport(13, 14);
                break;
            }
        }
    }

    if (eatenDots == 50) {
        for (auto &&ghost: entities) {
            if (ghost.get() != this && !(ghost->isOutHome())) {
                ghost->teleport(13, 14);
                break;
            }
        }
    }

    for (auto &&ghost: entities) {
        if (ghost.get() != this) {
            if (!ghost->isScattering())
                ghost->set_target(tileX, tileY);

            if (tileX == ghost->getTileX() && tileY == ghost->getTileY()) {
                if (ghost->isFrightened()) {
                    ghost->teleport(13, 14);
                    ghost->setFrightened(false);
                } else {
                    dead = true;
                    directions = {};
                    for (auto &&ghost1: entities)
                        ghost1->teleport(-2, -2);
                }
            }

        }
    }
    return true;
}