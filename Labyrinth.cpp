#include "Labyrinth.h"

Labyrinth::Labyrinth(const std::string& filename)
{
    std::ifstream fin;
    fin.open(filename);
    if (!fin.is_open())
    {
        std::cerr << "Ошибка открытия файла!\n";
    }
    for (auto&& tile : tiles)
        for (auto&& j : tile)
            fin >> j;
    fin.close();
}

int Labyrinth::getValue(int x, int y) const
{
    return tiles[x][y];
}

void Labyrinth::setValue(int x, int y, int value)
{
    tiles[x][y] = value;
}

bool Labyrinth::tileEntity(int x, int y) const
{
    return tiles[x][y] != 30 && tiles[x][y] != 26 && tiles[x][y] != 27;
}

bool Labyrinth::isIntersection(int x, int y) const
{
    return (x == 1 && y == 4) || (x == 6 && y == 4) || (x == 12 && y == 4) || (x == 15 && y == 4) || (x == 21 && y == 4) || (x == 26 && y == 4)
           || (x == 1 && y == 8) || (x == 6 && y == 8) || (x == 9 && y == 8) || (x == 12 && y == 8) || (x == 15 && y == 8) || (x == 18 && y == 8) || (x == 21 && y == 8) || (x == 26 && y == 8)
           || (x == 1 && y == 11) || (x == 6 && y == 11) || (x == 9 && y == 11) || (x == 12 && y == 11) || (x == 15 && y == 11) || (x == 18 && y == 11) || (x == 21 && y == 11) || (x == 26 && y == 11)
           || (x == 9 && y == 14) || (x == 12 && y == 14) || (x == 15 && y == 14) || (x == 18 && y == 14)
           || (x == 6 && y == 17) || (x == 9 && y == 17) || (x == 12 && y == 17) || (x == 15 && y == 17) || (x == 18 && y == 17) || (x == 21 && y == 17) || (x == 26 && y == 17)
           || (x == 9 && y == 20) || (x == 18 && y == 20)
           || (x == 1 && y == 23) || (x == 9 && y == 23) || (x == 6 && y == 23) || (x == 12 && y == 23) || (x == 15 && y == 23) || (x == 18 && y == 23) || (x == 21 && y == 23) || (x == 26 && y == 23)
           || (x == 1 && y == 26) || (x == 3 && y == 26) || (x == 6 && y == 26) || (x == 9 && y == 26) || (x == 12 && y == 26) || (x == 15 && y == 26) || (x == 18 && y == 26) || (x == 21 && y == 26) || (x == 24 && y == 26) || (x == 26 && y == 26)
           || (x == 1 && y == 29) || (x == 3 && y == 29) || (x == 6 && y == 29) || (x == 9 && y == 29) || (x == 12 && y == 29) || (x == 15 && y == 29) || (x == 18 && y == 29) || (x == 21 && y == 29) || (x == 24 && y == 29) || (x == 26 && y == 29)
           || (x == 1 && y == 32) || (x == 12 && y == 32) || (x == 15 && y == 32) || (x == 26 && y == 32)
           || (x == 13 && y == 14) || (x == 14 && y == 15);
}

