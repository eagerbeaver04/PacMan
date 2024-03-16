#include "Scene.h"
std::string filename = "labyrinth/Labirinth.txt";

void Scene::init()
{
    labyrinth =Labyrinth(filename);

    Entity* pacman = new PacMan();

    Entity* blinky = new Ghost(13, 14, 3, 4, 0.020f*2);
    Entity* pinky = new Ghost(13, 17, 23, 4, 0.017f*2);
    Entity* inky = new Ghost(11, 17, 26, 32, 0.014f*2);
    Entity* clyde = new Ghost(15, 17, 1, 32, 0.011f*2);

    blinky->teleport(15, 14);

    entities.push_back(pacman);
    entities.push_back(blinky);
    entities.push_back(pinky);
    entities.push_back(inky);
    entities.push_back(clyde);

    srand(time(NULL));

    delay = 0;
}

void Scene::draw(sf::RenderWindow* window)
{
    for (auto&& entity : entities)
        entity->draw(window, labyrinth);
}

void Scene::loop(sf::RenderWindow* window)
{
    for (auto&& entity : entities)
        if (!entity->render(delay, entities, window, labyrinth))
            Scene::init();
}

void Scene::create(sf::RenderWindow* window)
{
    for (int i = 0; i < Labyrinth::getSizeX(); i++)
    {
        for (int j = 0; j < Labyrinth::getSizeY(); j++)
        {
            Resources::LabyrinthPieces[labyrinth.getValue(i, j)]->setPosition(i * 16.0f, j * 16.0f);
            window->draw(*Resources::LabyrinthPieces[labyrinth.getValue(i, j)]);
        }
    }

    this->draw(window);
}

void Scene::key(int code)
{
    for (auto&& entity : entities)
        entity->key(code);
}

