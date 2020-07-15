#ifndef __ROOM_H
#define __ROOM_H

#include "../../Common.h"
#include "room_objects/Drone.h"
#include "room_objects/Furniture.h"

class Game;
class Terminal;

class Room {
    Shape roomShape;
    Position tom;
    Position jerry;
    Drone drone;

    friend class Drone;
    friend class Furniture;
    friend class Game;
    friend class Terminal;

    void loadRoomWithFreeSpaces();
    void drawFrameLine() const;
public:
    Room(int width, int length, Position tom, Position jerry);

    void print() const;

    void setRoomShape(int width, int length);

    void setTomPosition(Position position);

    void setJerryPosition(Position position);

    bool isInside(Position position);
    bool isValidPosition(Position position);
    bool isValidDronePosition(Position position);

    Position getTomPosition() const   { return tom; }
    Position getJerryPosition() const { return jerry; }

    Shape getRoomShape() const { return roomShape; }

    void addFurniture(Position positionNW, Shape shape);

    void setCanPaintPosition(Position position);
};

#endif