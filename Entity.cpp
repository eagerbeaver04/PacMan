#include "Entity.h"

void Entity::teleportTunnels()
{
    if (screenX == 0 && screenY == 17) {
        teleport(26, 17);
        return;
    }
    else if (screenX == 27 && screenY == 17)
        teleport(1, 17);
}