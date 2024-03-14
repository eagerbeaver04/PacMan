#pragma once
#include "Scene.h"

class Engine
{
private:
    static sf::RenderWindow window;
    static Scene game;

public:
    static void init();
    static bool isOpen();
    static void events();
    static void create();
};
