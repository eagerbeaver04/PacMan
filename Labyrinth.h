#include <string>
#include <iostream>
#include <fstream>

class Labyrinth
{
private:
    static const int SizeX = 28;
    static const int SizeY = 36;
    int tiles[SizeX][SizeY];
public:
    explicit Labyrinth(const std::string& filename);
    int getValue(int x, int y) const;
    void setValue(int x, int y, int value);
    bool tileEntity(int x, int y) const;
    bool isIntersection(int x, int y) const;
};

