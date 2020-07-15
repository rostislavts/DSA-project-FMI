#include "Drone.h"
#include "../Room.h"
#include <iostream>

Drone::Drone(Position p, Room& room) : room(room) {
    position = p; // "p" will be Tom's position,
                  // we are sure that it is valid !
}

bool Drone::canPaintAt(Position position) {
    int x = position.first;
    int y = position.second;
    return room.roomShape[x][y] == CAN_PAINT_SYMBOL;
}

void Drone::move(DIRECTION dir) {
    Position newPosition = position;
    switch (dir) {
        case (NORTH) : { newPosition.second -= 1;  break;  }
        case (SOUTH) : { newPosition.second += 1;  break;  }
        case (EAST)  : { newPosition.first  += 1;  break;  }
        case (WEST)  : { newPosition.first  -= 1;  break;  }
        default: return;
    }
    int newX = newPosition.first;
    int newY = newPosition.second;
    if (!room.isValidDronePosition(newPosition)) {
        std::cerr << "Wrong move, you cannot go there !!! " << std::endl;
        return;
    }
    if (newPosition == room.jerry) {
        std::clog << "Finish !!!" << std::endl;
        jerryIsFound = true;
        return;
    }
    position = newPosition;
    canPaint = canPaintAt(position);
    room.roomShape[newX][newY] = DRONE_SYMBOL;
}

void Drone::paint() {
    int x = position.first;
    int y = position.second;
    if (canPaint) {
        room.roomShape[x][y] = PAINTED_PLACE_SYMBOL;
    } else {
        std::cerr << "You cannot paint here !!!" << std::endl;
    }
}