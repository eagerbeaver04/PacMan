
#include "IMovable.h"

void IMovable::move(float x, float y) {
    screenX += x;
    screenY += y;

    if ((int) (screenX + 8) % 16 == 0 && (int) (screenY + 8) % 16 == 0) {
        tileX = (int) std::round((screenX - 8) / 16);
        tileY = (int) std::round((screenY - 8) / 16);
    }
}