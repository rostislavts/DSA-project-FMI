#ifndef __GAME_H
#define __GAME_H

#include "../models/room/Room.h"
#include <algorithm>

class Terminal;

class Game {
    Room& room;

    friend class Terminal;
public:
    Game(Room& room);

    void print() const { room.print(); }

    void printPath(Path path) const;
    void printCommands(std::vector<Command> droneCommands) const;

    int getLengthOfPath(Path path) const;

    int getNumOfPaints(Path path) const;

    int getNumOfTurns(Path path) const;

    std::vector<Command> getNeededCommands(Path path) const;
};

#endif
