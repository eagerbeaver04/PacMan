#include "Engine.h"

int main(int argc, char **argv) {
    Engine::init();

    while (Engine::isOpen()) {
        Engine::events();
        Engine::create();
    }

    system("pause");
    return 0;
}