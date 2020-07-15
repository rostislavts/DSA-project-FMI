#include "Room.h"

void Room::loadRoomWithFreeSpaces() {
    int width  = roomShape.size();
    int length = roomShape[0].size();
    for (int y = 0; y < length; y++) {
        for (int x = 0; x < width; x++) {
            roomShape[x][y] = FREE_SPACE_SYMBOL;
        }
    }
}

Room::Room(int width, int length, Position tom, Position jerry) : drone(tom, *this) {
    setRoomShape(width, length);
    loadRoomWithFreeSpaces();
    setTomPosition(tom);
    setJerryPosition(jerry);
}

void Room::drawFrameLine() const { // Like this * * * * * * * * * *
    int width = roomShape.size();
    for (int x = 0 ; x < width + 2; x++) {
        std::cout << '*' << ' ';
    }
    std::cout << std::endl;
}

void Room::print() const {
    int width   = roomShape.size();
    int length  = roomShape[0].size();

    drawFrameLine();
    for (int y = 0; y < length; y++) {
        for (int x = -1; x < width + 1; x++) {
            if (x == -1 || x == width) {
                std::cout << '*' << ' ';
            } else {
                std::cout << roomShape[x][y] << ' ';
            }
        }
        std::cout << std::endl;
    }
    drawFrameLine();
}

void Room::setRoomShape(int width, int length) {
    for (int i = 0; i < width; i++) {
        roomShape.push_back(std::vector<char>(length));
    }
}

bool Room::isInside(Position position) {
    int x = position.first;
    int y = position.second;
    return x >= 0 && x < roomShape.size() &&
             y >= 0 && y < roomShape[x].size();
}

bool Room::isValidPosition(Position position) {
    int x = position.first;
    int y = position.second;
    return isInside(position) && roomShape[x][y] == FREE_SPACE_SYMBOL;
}

bool Room::isValidDronePosition(Position position) {
    int x = position.first;
    int y = position.second;
    return isInside(position) &&
           (roomShape[x][y] == CAN_PAINT_SYMBOL ||
           roomShape[x][y] == FREE_SPACE_SYMBOL ||
           roomShape[x][y] == JERRY_SYMBOL);
}

void Room::setTomPosition(Position position) {
    if (!isValidPosition(position)) {
        std::cerr << "Wrong Tom position !!!" << std::endl;
        tom = {-1, -1};
        return;
    }
    tom = position;
    int x = position.first;
    int y = position.second;
    roomShape[x][y] = TOM_SYMBOL;
}

void Room::setJerryPosition(Position position) {
    if (!isValidPosition(position)) {
        std::cerr << "Wrong Jerry position !!!" << std::endl;
        jerry = {-1, -1};
        return;
    }
    jerry = position;
    int x = position.first;
    int y = position.second;
    roomShape[x][y] = JERRY_SYMBOL;
}

void Room::setCanPaintPosition(Position position) {
    int x = position.first;
    int y = position.second;
    roomShape[x][y] = CAN_PAINT_SYMBOL;
}

void Room::addFurniture(Position positionNW, Shape shape) {
    Furniture furniture(positionNW, shape);
    furniture.loadInTheRoom(*this);
}
