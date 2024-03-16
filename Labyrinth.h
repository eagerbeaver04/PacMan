#pragma once
#include <string>
#include <iostream>
#include <fstream>

class Labyrinth
{
private:
    static const int sizeX = 28;
    static const int sizeY = 36;
    int tiles[sizeX][sizeY];
public:
    explicit Labyrinth(const std::string& filename);
    Labyrinth() = default;
    Labyrinth(Labyrinth&&) = default;
    Labyrinth& operator = (Labyrinth&&) = default;
    Labyrinth(const Labyrinth&) = default;
    Labyrinth& operator = (const Labyrinth&) = default;
    [[nodiscard]] int getValue(int x, int y) const;
    void setValue(int x, int y, int value);
    [[nodiscard]] bool tileEntity(int x, int y) const;
    [[nodiscard]] bool isIntersection(int x, int y) const;
    static int getSizeX()  {return sizeX;}
    static int getSizeY() {return sizeY;}

};

