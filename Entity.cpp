#include "Entity.h"

void Entity::teleportTunnels()
{
    if (tileX == 0 && tileY == 17)
        teleport(26, 17);
    else if (tileX == 27 && tileY == 17)
        teleport(1, 17);
}