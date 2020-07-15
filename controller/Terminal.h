#ifndef __TERMINAL_H
#define __TERMINAL_H

#include "../Common.h"
#include "Game.h"
#include "../models/room/room_loader/RoomLoader.h"
#include "../view/CommandTree.h"
#include "../models/graph/Graph.h"

class Terminal {
    std::map<std::string, DIRECTION> flyCommands;
    std::map<char, sf::Texture> toTexture;

    void loadFlyCommands();

    void printShortestPaths(Game& game, std::vector<Path> paths);

    void printMaxPaintsMinTurnsPath(Game& game, std::vector<Path> paths);

    void printMrJinxPaths(Game& game, std::vector<Path> paths);

    void printAllInfo(Game& game);

    void fillWithEmptyCells(std::vector<std::vector<sf::RectangleShape> >& recs, int roomWidth, int roomHeight);

    void updateCells(std::vector<std::vector<sf::RectangleShape> >& recs, Room& room);

    void loadCharToTexture();

    void runAnimation(sf::RenderWindow& window, Game& game, std::vector<std::vector<sf::RectangleShape> >& recs);

public:
    void run();
};

#endif
