#include <sstream>
#include "models/room/Room.h"
#include "controller/Terminal.h"
#include "view/CommandTree.h"

void testRoom() {
    Shape roomShape;
    int m = 10;
    int n = 10;
    Room room(m, n, {0, 0}, {2, 3});

    /*
    room.getDrone().move(SOUTH);
    room.getDrone().move(EAST);
    room.getDrone().move(SOUTH);
    room.getDrone().move(SOUTH);
    */
    //room.print();

    Position posNW = {0, 5};
    Shape furnShape = { {'1', ' '}, {'1', '1'}, {'1', '1'}, {'1', ' '}, {'1', ' '}    } ;


    room.addFurniture(posNW, furnShape);

    room.setCanPaintPosition( {2, 8} );


    room.print();
}

void testTerminal() {
    std::stringstream ss("4 4\n0 2\n3 0\n2 1\n2 1\n11\n 1\n===\n1 3\n1\n===\n1 1");
    Terminal t;
    //Game game = t.loadGame(ss);
    //game.getRoom().print();

    //Game game = t.loadGame(ss);
    //game.getRoom().print();
}

void treeTest() {
    CommandTree tree;
    std::vector<Command> commands;
    commands.push_back("[ N ]");
    commands.push_back("[ N ]");
    commands.push_back("[ N ]");
    commands.push_back("[ S ]");
    commands.push_back("[ N ]");
    commands.push_back("[ S ]");

    tree.loadCommandPath(commands, 0);


    std::vector<Command> commands1;
    commands1.push_back("[ N ]");
    commands1.push_back("[ N ]");
    commands1.push_back("[ N ]");
    commands1.push_back("[ N ]");
    commands1.push_back("[ N ]");
    commands1.push_back("[ N ]");

    tree.loadCommandPath(commands1, 1);


    std::vector<Command> commands2;
    commands2.push_back("[ S ]");
    commands2.push_back("[ W ]");
    commands2.push_back("[ E ]");
    commands2.push_back("[ N ]");
    commands2.push_back("[ S ]");
    commands2.push_back("[ W ]");

    tree.loadCommandPath(commands2, 2);

    tree.print();
}


int main() {
    //testRoom();
    //testTerminal();

    Terminal terminal;
    terminal.run();


    //treeTest();
    return 0;
}


int mains() {

    // 40x40
    sf::RenderWindow window(sf::VideoMode(200, 160), "SFML works!");

    sf::Texture Tom;
    if (!Tom.loadFromFile("images/Tom.png")) {
        std::cout << "Kofti";
    }

    sf::Texture Jerry;
    if (!Jerry.loadFromFile("images/Jerry.png")) {
        std::cout << "Kofti";
    }
    sf::Texture Empty;
    if (!Empty.loadFromFile("images/Empty.png")) {
        std::cout << "Kofti";
    }
    sf::Texture Drone;
    if (!Drone.loadFromFile("images/Drone.png")) {
        std::cout << "Kofti";
    }
    sf::Texture Sofa;
    if (!Sofa.loadFromFile("images/Sofa.png")) {
        std::cout << "Kofti";
    }
    sf::Texture CanPaintSpot;
    if (!CanPaintSpot.loadFromFile("images/CanPaintSpot.png")) {
        std::cout << "Kofti";
    }
    sf::Texture PaintedSpot;
    if (!PaintedSpot.loadFromFile("images/PaintedSpot.png")) {
        std::cout << "Kofti";
    }

    std::vector< std::vector <sf::RectangleShape> > recs;

    for (int kI = 0; kI < 4; ++kI) { // y
        recs.push_back(std::vector<sf::RectangleShape>());
        for (int kJ = 0; kJ < 5; ++kJ) { // x
            recs[kI].push_back(sf::RectangleShape(sf::Vector2f(40, 40)));
            recs[kI][kJ].setTexture(&Empty);
            recs[kI][kJ].setPosition(40*kJ,40*kI);
        }
    }

    // y x
    recs[0][3].setTexture(&Tom);
    recs[2][0].setTexture(&Jerry);
    recs[0][2].setTexture(&Drone);
    recs[0][1].setTexture(&Drone);
    recs[1][1].setTexture(&CanPaintSpot);
    recs[1][0].setTexture(&PaintedSpot);
    recs[2][1].setTexture(&Sofa);
    recs[2][2].setTexture(&Sofa);
    recs[3][2].setTexture(&Sofa);
    recs[1][3].setTexture(&Sofa);


    while (window.isOpen()) {
        sf::Event event;


        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (int kI = 0; kI < 4; ++kI) {
            for (int kJ = 0; kJ < 5; ++kJ) {
                window.draw(recs[kI][kJ]);
            }
        }
        window.display();


    }

    return 0;
}


