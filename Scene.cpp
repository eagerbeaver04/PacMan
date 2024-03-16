#include "Scene.h"
std::string filename = "labyrinth/Labirinth.txt";

void Scene::init()
{
    labyrinth =Labyrinth(filename);

    auto pacman = std::unique_ptr<Entity>(new PacMan());

    auto blinky = std::unique_ptr<Entity>(new Ghost(13, 14, 3, 4, 0.020f*2));
    auto pinky = std::unique_ptr<Entity>(new Ghost(13, 17, 23, 4, 0.017f*2));
    auto inky = std::unique_ptr<Entity>(new Ghost(11, 17, 26, 32, 0.014f*2));
    auto clyde = std::unique_ptr<Entity>(new Ghost(15, 17, 1, 32, 0.011f*2));

    blinky->teleport(15, 14);

    entities.push_back(std::move(pacman));
    entities.push_back(std::move(blinky));
    entities.push_back(std::move(pinky));
    entities.push_back(std::move(inky));
    entities.push_back(std::move(clyde));

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

