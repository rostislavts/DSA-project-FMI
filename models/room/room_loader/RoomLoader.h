#ifndef __ROOMLOADER_H
#define __ROOMLOADER_H

#include "../../../Common.h"
#include "../../../controller/Game.h"

class RoomLoader {
    static void loadFurniture(std::istream& is, int numOfFurniture, Room& room);
    static void loadCanPaintPositions(std::istream& is, int numOfCanPaintPositions, Room& room);

    static std::pair<int, int> readLineWithTwoIntegers(std::istream& is);

    static Shape reverseShape(Shape reversedShape);

public:
    static Room createRoom(std::istream& is);
    static void loadFurnitureAndCanPaintPositions(std::istream& is, Room& room);
};

#endif