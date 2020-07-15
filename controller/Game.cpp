#include "Game.h"

Game::Game(Room& room) : room(room) {}

std::ostream& operator<<(std::ostream& os, Position p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

void Game::printPath(Path path) const {
    while(!path.empty()) {
        Position currentPos = path.front();
        path.pop();
        if (path.empty()) {
            std::cout << currentPos << std::endl;
            return;
        }
        std::cout << currentPos << " -> ";
    }
}

int Game::getLengthOfPath(Path path) const {
    return path.size() - 1;
}

int Game::getNumOfPaints(Path path) const {
    int counter = 0;
    while(!path.empty()) {
        Position p = path.front();
        path.pop();
        if (room.getRoomShape()[p.first][p.second] == CAN_PAINT_SYMBOL) {
            counter++;
        }
    }
    return counter;
}

int Game::getNumOfTurns(Path path) const {
    if (path.size() < 3) { //  *
        return 0;          //  * *   * * * *
    }                      //    * * *
    Position prevPrev = path.front();
    path.pop();
    Position prev     = path.front();
    path.pop();
    int counter = 0;
    while(!path.empty()) {
        Position curr = path.front();
        path.pop();
        if (curr.first != prevPrev.first && curr.second != prevPrev.second) {
            counter++;
        }
        prevPrev = prev;
        prev     = curr;
    }
    return counter;
}

void Game::printCommands(std::vector<Command> droneCommands) const {
    for (int i = 0; i < droneCommands.size(); i++) {
        if (i == droneCommands.size() - 1) {
            std::cout << droneCommands[i] << std::endl;
            return;
        }
        std::cout << droneCommands[i] << " --> ";
    }
}

std::vector<Command> Game::getNeededCommands(Path path) const {
    std::vector<Command> result;
    if (path.empty()) {
        return result;
    }
    Position prev = path.front();
    path.pop();
    while (!path.empty()) {
        Position curr = path.front();
        path.pop();

        if (room.getRoomShape()[prev.first][prev.second] == CAN_PAINT_SYMBOL) {
            result.push_back("[ P ]");
        }

        if (curr.first == prev.first + 1) {
            result.push_back("[ E ]");
        } else if (curr.first == prev.first - 1) {
            result.push_back("[ W ]");
        } else if (curr.second == prev.second + 1) {
            result.push_back("[ S ]");
        } else if (curr.first == prev.first - 1) {
            result.push_back("[ N ]");
        }
        prev = curr;
    }
    return result;
}
