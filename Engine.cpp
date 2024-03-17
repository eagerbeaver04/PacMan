#include "Engine.h"

sf::RenderWindow Engine::window;
Scene Engine::game;

void Engine::init() {
    Resources::load();
    window.create(sf::VideoMode(448, 596), "PacMan Game");
    game.init();
}

bool Engine::isOpen() {
    return window.isOpen();
}

void Engine::events() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                game.key(event.key.code);
                break;
        }
    }
    game.loop(&window);
}

void Engine::create() {
    window.clear(sf::Color::Black);
    game.create(&window);
    window.display();
}
