#include "Furniture.h"
#include "../Room.h"

Furniture::Furniture(Position positionNW, Shape shape) : positionNW(positionNW), shape(shape) {}

bool Furniture::canLoadInTheRoom(Room& room) {
    int shapeWidth = shape.size();
    int shapeHeight = shape[0].size();

    int xNW = positionNW.first;
    int yNW = positionNW.second;

    if (xNW + shapeWidth > room.roomShape.size() ||
        yNW + shapeHeight > room.roomShape[0].size()) {
        return false;
    }

    for (int x = xNW; x < shapeWidth + xNW; x++) {
        for (int y = yNW; y < shapeHeight + yNW; y++) {
            if (shape[x - xNW][y - yNW] == FURNITURE_SYMBOL && room.roomShape[x][y] != FREE_SPACE_SYMBOL) {
                return false;
            }
        }
    }
    return true;
}

void Furniture::loadInTheRoom(Room& room) {
    if (!canLoadInTheRoom(room)) {
        std::cerr << "This furniture cannot be loaded in the room !!!" << std::endl;
        return;
    }

    int shapeWidth = shape.size();
    int shapeHeight = shape[0].size();

    int xNW = positionNW.first;
    int yNW = positionNW.second;

    for (int x = 0; x < shapeWidth; x++) {
        for (int y = 0; y < shapeHeight; y++) {
            if (shape[x][y] == FURNITURE_SYMBOL) {
                room.roomShape[x + xNW][y + yNW] = FURNITURE_SYMBOL;
            }
        }
    }
}