#include <fstream>
#include "Terminal.h"

void Terminal::loadFlyCommands() {
    flyCommands["N"] = NORTH;
    flyCommands["S"] = SOUTH;
    flyCommands["E"] = EAST;
    flyCommands["W"] = WEST;
}

void Terminal::printShortestPaths(Game& game, std::vector<Path> paths) {
    std::cout << std::endl;
    std::cout << "Shortest paths : " << std::endl;

    if (paths.empty()) {
        std::cout << "No paths !" << std::endl;
        return;
    }

    CommandTree tree;
    for (int i = 0; i < paths.size(); i++) {
        tree.loadCommandPath(game.getNeededCommands(paths[i]), i);
    }
    tree.print();

    int index;
    do {
        std::cout << "Enter an index\n>";
        std::cin >> index;
    } while (index < 0 || index >= paths.size());

    std::cout << "Needed commands:\n";
    game.printCommands(game.getNeededCommands(paths[index]));
    std::cout << "Length of the path: " << game.getLengthOfPath(paths[index]) << std::endl;
    std::cout << "Number of paints: " << game.getNumOfPaints(paths[index]) << std::endl;
    std::cout << "Number of turns: " << game.getNumOfTurns(paths[index]) << std::endl;
}

void Terminal::printMaxPaintsMinTurnsPath(Game& game, std::vector<Path> paths) {
    std::cout << std::endl;
    std::cout << "Path with max paints and min turns : " << std::endl;

    if (paths.empty()) {
        std::cout << "No paths !" << std::endl;
        return;
    }
    game.printCommands(game.getNeededCommands(paths[0]));
}

void Terminal::printMrJinxPaths(Game& game, std::vector<Path> paths) {
    std::cout << std::endl;
    std::cout << "Mr Jinx paths : " << std::endl;

    if (paths.empty()) {
        std::cout << "No paths !" << std::endl;
        return;
    }
    game.printCommands(game.getNeededCommands(paths[0]));
    game.printCommands(game.getNeededCommands(paths[1]));
}

void Terminal::printAllInfo(Game& game) {
    Room& room = game.room;

    Graph graph(room);
    std::vector<Path> shortestPaths = graph.findAllShortestPaths(room.getTomPosition(), room.getJerryPosition());
    std::vector<Path> allPaths = graph.findAllPaths(room.getTomPosition(), room.getJerryPosition());

    game.print();

    printShortestPaths(game, shortestPaths);

    std::vector<Path> maxPaintsMinTurnsPaths = graph.findAllMaxPaintsAndMinTurnsPaths(allPaths);

    printMaxPaintsMinTurnsPath(game, maxPaintsMinTurnsPaths);

    std::vector<Path> mrJinxPaths = graph.findAllMrJinxPaths(allPaths);

    printMrJinxPaths(game, mrJinxPaths);
}

void Terminal::loadCharToTexture() {
    sf::Texture Tom;
    Tom.loadFromFile("images/Tom.png");
    sf::Texture Jerry;
    Jerry.loadFromFile("images/Jerry.png");
    sf::Texture Empty;
    Empty.loadFromFile("images/Empty.png");
    sf::Texture Drone;
    Drone.loadFromFile("images/Drone.png");
    sf::Texture Sofa;
    Sofa.loadFromFile("images/Sofa.png");
    sf::Texture CanPaintSpot;
    CanPaintSpot.loadFromFile("images/CanPaintSpot.png");
    sf::Texture PaintedSpot;
    PaintedSpot.loadFromFile("images/PaintedSpot.png");

    toTexture[FREE_SPACE_SYMBOL] = Empty;
    toTexture[TOM_SYMBOL] = Tom;
    toTexture[JERRY_SYMBOL] = Jerry;
    toTexture[PAINTED_PLACE_SYMBOL] = PaintedSpot;
    toTexture[DRONE_SYMBOL] = Drone;
    toTexture[CAN_PAINT_SYMBOL] = CanPaintSpot;
    toTexture[FURNITURE_SYMBOL] = Sofa;
}

void Terminal::fillWithEmptyCells(std::vector<std::vector<sf::RectangleShape> >& recs, int roomWidth, int roomHeight) {
    for (int y = 0; y < roomHeight; y++) {
        recs.push_back(std::vector<sf::RectangleShape>());
        for (int x = 0; x < roomWidth; x++) {
            recs[y].push_back(sf::RectangleShape(sf::Vector2f(40, 40)));
            recs[y][x].setTexture(&toTexture[FREE_SPACE_SYMBOL]);
            recs[y][x].setPosition(40 * x,40 * y);
        }
    }
}

void Terminal::updateCells(std::vector<std::vector<sf::RectangleShape> >& recs, Room& room) {
    int roomWidth = room.getRoomShape().size();
    int roomHeight = room.getRoomShape()[0].size();

    for (int y = 0; y < roomHeight; y++) {
        for (int x = 0; x < roomWidth; x++) {
            char currentSymbol = room.getRoomShape()[x][y];
            recs[y][x].setTexture(&toTexture[currentSymbol]);
        }
    }
}

void Terminal::runAnimation(sf::RenderWindow& window, Game& game, std::vector<std::vector<sf::RectangleShape> >& recs) {
    Room& room = game.room;
    int roomWidth = room.getRoomShape().size();
    int roomHeight = room.getRoomShape()[0].size();

    std::string userInput;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        for (int i = 0; i < roomHeight; i++) {
            for (int j = 0; j < roomWidth; j++) {
                window.draw(recs[i][j]);
            }
        }
        window.display();

        std::cout << "Enter a command\n> ";
        std::cin >> userInput;

        if (userInput == "exit") {
            return;
        } else if (userInput == "P") {
            game.room.drone.paint();
        } else if (flyCommands.count(userInput)) {
            game.room.drone.move(flyCommands[userInput]);
            if (game.room.drone.isFound()) {
                return;
            }
        } else {
            std::clog << "Invalid command!!!\n";
        }

        updateCells(recs, room);
    }
}


void Terminal::run() {
    loadFlyCommands();

    std::string fileName;
    std::ifstream ifs;
    do {
        std::cout << "Enter a file name\n> ";
        std::cin >> fileName;
        ifs.open(fileName);
    } while (ifs.fail());

    Room room = RoomLoader::createRoom(ifs);
    RoomLoader::loadFurnitureAndCanPaintPositions(ifs, room);
    Game game(room);
    ifs.close();

    printAllInfo(game);

    int roomWidth = room.getRoomShape().size();
    int roomHeight = room.getRoomShape()[0].size();
    sf::RenderWindow window(sf::VideoMode(roomWidth * 40, roomHeight * 40), "Tom and Jerry");

    std::vector<std::vector<sf::RectangleShape> > recs;

    loadCharToTexture();

    fillWithEmptyCells(recs, roomWidth, roomHeight);

    std::cout << std::endl;
    game.print();

    updateCells(recs, room);

    runAnimation(window, game, recs);
}