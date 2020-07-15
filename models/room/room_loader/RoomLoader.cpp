#include <fstream>
#include "RoomLoader.h"

std::pair<int, int> RoomLoader::readLineWithTwoIntegers(std::istream& is) {
    std::string line;
    std::getline(is, line);
    int idxOfSpace = line.find_first_of(' ');
    std::string firstIntStr = line.substr(0, idxOfSpace);
    line = line.erase(0, idxOfSpace + 1);
    std::string secondIntStr = line;

    int first = std::stoi(firstIntStr);
    int second = std::stoi(secondIntStr);
    return { first, second };
}

Room RoomLoader::createRoom(std::istream& is) {
    // line 1 - room width and length
    std::pair<int, int> roomSpecs = readLineWithTwoIntegers(is);

    // line 2 - Jerry's position
    Position jerry = readLineWithTwoIntegers(is);

    // line 3 - Tom's position
    Position tom = readLineWithTwoIntegers(is);

    // Now we can create the room !!!
    int width = roomSpecs.first;
    int length = roomSpecs.second;
    return Room(width, length, tom, jerry);
}

Shape RoomLoader::reverseShape(Shape reversedShape) { // Because my Ox is vertical, Oy - horizontal
    // Convert
    // { {'1', '1', '1', '1', '1'} {' ', '1', '1', ' ', ' ' } }
    // to
    // { {'1', ' '}, {'1', '1'}, {'1', '1'}, {'1', ' '}, {'1', ' '} }

    int numOfRowsInShape = reversedShape.size();
    int numOfColsInShape = reversedShape[0].size();

    Shape shape;
    std::vector<char> newCol(numOfRowsInShape);
    for (int i = 0; i < numOfColsInShape; i++) {
        shape.push_back(newCol);
    }

    for (int i = 0; i < numOfRowsInShape; i ++) {
        for (int j = 0; j < numOfColsInShape; j++) {
            shape[j][i] = reversedShape[i][j];
        }
    }
    return shape;
}

void RoomLoader::loadFurniture(std::istream& is, int numOfFurniture, Room& room) {
    for (int i = 0; i < numOfFurniture; i++) {
        Position positionNW = readLineWithTwoIntegers(is);

        std::string currentLine;

        Shape reversedShape;

        std::getline(is, currentLine);
        while (currentLine != "===") {

            std::vector<char> row;
            for (char c : currentLine) {
                row.push_back(c);
            }
            reversedShape.push_back(row);

            std::getline(is, currentLine);
        }
        Shape shape = reverseShape(reversedShape);
        room.addFurniture(positionNW, shape);
    }
}

void RoomLoader::loadCanPaintPositions(std::istream& is, int numOfCanPaintPos, Room& room) {
    for (int i = 0; i < numOfCanPaintPos; i++) {
        Position canPaintPosition = readLineWithTwoIntegers(is);
        room.setCanPaintPosition(canPaintPosition);
    }
}

void RoomLoader::loadFurnitureAndCanPaintPositions(std::istream& is, Room& room) {
    // line 4 - first -> numOfFurniture, second -> numOfCanPaintPositions
    std::pair<int, int> numOfFurnitureAndCanPaintPos = readLineWithTwoIntegers(is);

    int numOfFurniture = numOfFurnitureAndCanPaintPos.first;
    int numOfCanPaintPos = numOfFurnitureAndCanPaintPos.second;

    loadFurniture(is, numOfFurniture, room);
    loadCanPaintPositions(is, numOfCanPaintPos, room);
}