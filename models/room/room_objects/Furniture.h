#ifndef __FURNITURE_H
#define __FURNITURE_H

#include "../../../Common.h"

class Room;

class Furniture {
    Position positionNW;
    Shape shape;

    bool canLoadInTheRoom(Room& room);
public:
    Furniture(Position positionNW, Shape shape);

    void loadInTheRoom(Room& room);
};

#endif