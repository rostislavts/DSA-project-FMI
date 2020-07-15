#include "Graph.h"

Graph::Graph(Room& room) : room(room) {
    convertGridToGraph();
}

int Graph::getIndex(Position position) {
    // * * * * * *
    // * 0 1 2 3 *   y * width + x
    // * 4 5 6 7 *
    // * * * * * *
    return position.second * room.getRoomShape().size() + position.first;
}

int Graph::getPaints(Path path) {
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

void Graph::convertGridToGraph() {
    int width = room.getRoomShape().size();
    int height = room.getRoomShape()[0].size();

    adjacencyList = std::vector<std::vector<VertexAndWeight> >(width * height);

    for (int col = 0; col < width; col++) {
        for (int row = 0; row < height; row++) {
            int index = row * width + col;
            for (int dx : {-1, 0, 1}) {
                for (int dy : {-1, 0, 1}) {
                    int sum = std::abs(dx) + std::abs(dy);
                    if (sum == 1) {
                        Position newPosition = {col + dx, row + dy};
                        if (room.isValidDronePosition(newPosition)) {
                            adjacencyList[index].push_back({newPosition, 1});
                        }
                    }
                }
            }
        }
    }
}

std::vector<Path> Graph::findAllShortestPaths(Position start, Position end) {
    std::vector<Path> resultPaths;

    std::priority_queue<QueueElement,
                        std::vector<QueueElement>,
                        std::greater<> > queue;


    QueueElement startBox;
    startBox.currentPath.push_back(start);
    startBox.distance = 0;

    queue.push(startBox);

    while(!queue.empty()) {

        QueueElement currentBox = queue.top();
        queue.pop();

        Position currentPosition = currentBox.currentPath.back();

        if (currentPosition == end) {
            Path newPath;
            for (Position p : currentBox.currentPath) {
                newPath.push(p);
            }

            if (!resultPaths.empty()) {
                int minDistance = resultPaths[0].size();
                if (newPath.size() > minDistance) {
                    return resultPaths;
                }
            }

            resultPaths.push_back(newPath);
            continue;
        }

        for (VertexAndWeight vw : adjacencyList[getIndex(currentPosition)]) {
            if (!currentBox.isMember(vw.first)) {

                QueueElement newBox = currentBox;
                newBox.currentPath.push_back(vw.first);
                newBox.distance += vw.second;

                queue.push(newBox);
            }
        }
    }
}

std::vector<Path> Graph::findAllPaths(Position start, Position end) {
    std::vector<Path> resultPaths;

    std::queue<QueueElement> queue;

    QueueElement startBox;
    startBox.currentPath.push_back(start);
    startBox.distance = 0;

    queue.push(startBox);

    while(!queue.empty()) {

        QueueElement currentBox = queue.front();
        queue.pop();

        Position currentPosition = currentBox.currentPath.back();

        if (currentPosition == end) {
            Path newPath;
            for (Position p : currentBox.currentPath) {
                newPath.push(p);
            }
            resultPaths.push_back(newPath);
            continue;
        }

        for (VertexAndWeight vw : adjacencyList[getIndex(currentPosition)]) {
            if (!currentBox.isMember(vw.first)) {

                QueueElement newBox = currentBox;
                newBox.currentPath.push_back(vw.first);
                newBox.distance += vw.second;

                queue.push(newBox);
            }
        }
    }
    return resultPaths;
}

int Graph::getMaxNumOfPaints(std::vector<Path>& paths) {
    int max = 0;
    for (Path p : paths) {
        int current = getPaints(p);
        if (current > max) {
            max = current;
        }
    }
    return max;
}

int Graph::getTurns(Path path) {
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

int Graph::getMinNumOfTurns(std::vector<Path>& paths) {
    int min = getTurns(paths[0]);
    for (Path p : paths) {
        int current = getTurns(p);
        if (current < min) {
            min = current;
        }
    }
    return min;
}

std::vector<Path> Graph::filterPathsByMaxNumOfPaints(std::vector<Path>& paths, int maxNumOfPaints) {
    std::vector<Path> resultPaths;
    for (Path p : paths) {
        if (getPaints(p) == maxNumOfPaints) {
            resultPaths.push_back(p);
        }
    }
    return resultPaths;
}

std::vector<Path> Graph::filterPathsByMinTurns(std::vector<Path>& paths, int minNumOfTurns) {
    std::vector<Path> resultPaths;
    for (Path p : paths) {
        if (getTurns(p) == minNumOfTurns) {
            resultPaths.push_back(p);
        }
    }
    return resultPaths;
}

std::vector<Path> Graph::findAllMaxPaintsAndMinTurnsPaths(std::vector<Path>& allPaths) {
    int maxNumOfPaints = getMaxNumOfPaints(allPaths);

    std::vector<Path> filteredPathsByMaxPaints = filterPathsByMaxNumOfPaints(allPaths, maxNumOfPaints);

    int minNumOfTurns = getMinNumOfTurns(filteredPathsByMaxPaints);

    return filterPathsByMinTurns(filteredPathsByMaxPaints, minNumOfTurns);
}

bool Graph::mrJinxCondition(Path a, Path b) {
    return a.size() == b.size() && dontHaveSamePosAtSameTime(a, b) && dontCoverSamePaintPos(a, b);
}

bool Graph::dontHaveSamePosAtSameTime(Path a, Path b) {
    // We call this function only if we know that 'a' and 'b' have same length

    // We should remove start and end positions, they will always be Tom's pos and Jerry's pos
    a.pop();
    b.pop();

    while (!a.empty()) {
        Position currA = a.front();
        Position currB = b.front();
        a.pop();
        b.pop();

        if (!a.empty() && currA == currB) { // Same position at same time and thats not the end position
            return false;
        }
    }
    return true;
}

bool Graph::dontCoverSamePaintPos(Path a, Path b) {
    std::vector<Position> visitedPaintPositions;

    while (!a.empty()) {
        Position currA = a.front();
        a.pop();

        if (room.getRoomShape()[currA.first][currA.second] == CAN_PAINT_SYMBOL) {
            visitedPaintPositions.push_back(currA);
        }
    }

    while (!b.empty()) {
        Position currB = b.front();
        b.pop();

        if (room.getRoomShape()[currB.first][currB.second] == CAN_PAINT_SYMBOL &&
            std::find(visitedPaintPositions.begin(), visitedPaintPositions.end(), currB) != visitedPaintPositions.end()) {
            return false;
        }
    }
    return true;
}

std::vector<Path> Graph::findAllMrJinxPaths(std::vector<Path> allPaths) {
    std::sort(allPaths.begin(), allPaths.end(), [](Path const& a, Path const& b) -> bool {return a.size() < b.size();});

    std::vector<Path> result;

    int minPossibleLength = 0;

    for (int i = 0; i < allPaths.size() - 1; i++) {
        if (minPossibleLength != 0 && allPaths[i].size() > minPossibleLength) {
            return findPairWithMaxPaints(result);
        }

        for (int j = i + 1; j < allPaths.size() && allPaths[i].size() == allPaths[j].size(); j++) {
            if (mrJinxCondition(allPaths[i], allPaths[j])) {
                result.push_back(allPaths[i]);
                result.push_back(allPaths[j]);

                minPossibleLength = result[0].size();
            }
        }
    }
    return result; // aka {}
}

int Graph::maxSumOfPaintsOfPairPaths(std::vector<Path>& mrJinxPaths) {
    int maxPaintsOfPairPaths = 0;

    for (int i = 0; i < mrJinxPaths.size() - 1; i+=2) {
        int sumOfPaints = getPaints(mrJinxPaths[i]) + getPaints(mrJinxPaths[i + 1]);

        if (sumOfPaints > maxPaintsOfPairPaths) {
            maxPaintsOfPairPaths = sumOfPaints;
        }
    }

    return maxPaintsOfPairPaths;
}

std::vector<Path> Graph::findPairWithMaxPaints(std::vector<Path>& mrJinxPaths) {
    int maxPaintsOfPairPaths = maxSumOfPaintsOfPairPaths(mrJinxPaths);

    for (int i = 0; i < mrJinxPaths.size() - 1; i+=2) {
        int sumOfPaints = getPaints(mrJinxPaths[i]) + getPaints(mrJinxPaths[i + 1]);

        if (sumOfPaints == maxPaintsOfPairPaths) {
            return { mrJinxPaths[i], mrJinxPaths[i + 1] };
        }
    }

    return {};
}
