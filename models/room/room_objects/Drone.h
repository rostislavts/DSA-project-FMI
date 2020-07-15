#ifndef __DRONE_H
#define __DRONE_H

#include <utility>
#include "../../../Common.h"

enum DIRECTION {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

class Room;

class Drone {
    Position position;
    bool canPaint;
    bool jerryIsFound = false; // TODO : Ask about it !!!
    Room& room;

    bool canPaintAt(Position position);

public:
    Position getPosition() const { return position; }

    Drone(Position p, Room& room);

    void move(DIRECTION dir);

    bool isFound() const { return jerryIsFound; }

    void paint();
};

#endif