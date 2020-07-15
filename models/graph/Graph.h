#ifndef __GRAPH_H
#define __GRAPH_H

#include "../../Common.h"
#include "../room/Room.h"

struct QueueElement {
    std::list<Position> currentPath;
    int distance;

    bool operator>(QueueElement const& el) {
        return distance > el.distance;
    }

    bool isMember(Position position) {
        for (Position p : currentPath) {
            if (p == position) {
                return true;
            }
        }
        return false;
    }
};

class Graph {
    std::vector<std::vector<VertexAndWeight> > adjacencyList;
    Room& room;

    int getIndex(Position position);
    int getPaints(Path path);

    int getTurns(Path path);

    void convertGridToGraph();

    int getMaxNumOfPaints(std::vector<Path>& paths);

    int getMinNumOfTurns(std::vector<Path>& paths);

    std::vector<Path> filterPathsByMaxNumOfPaints(std::vector<Path>& paths, int maxNumOfPaints);

    std::vector<Path> filterPathsByMinTurns(std::vector<Path>& paths, int minNumOfTurns);

    bool mrJinxCondition(Path a, Path b);
    bool dontHaveSamePosAtSameTime(Path a, Path b);
    bool dontCoverSamePaintPos(Path a, Path b);

    std::vector<Path> findPairWithMaxPaints(std::vector<Path>& mrJinxPaths);
    int maxSumOfPaintsOfPairPaths(std::vector<Path>& mrJinxPaths);

public:
    Graph(Room& room);

    std::vector<Path> findAllShortestPaths(Position start, Position end);

    std::vector<Path> findAllPaths(Position start, Position end);

    std::vector<Path> findAllMaxPaintsAndMinTurnsPaths(std::vector<Path>& allPaths);

    std::vector<Path> findAllMrJinxPaths(std::vector<Path> allPaths);
};

#endif