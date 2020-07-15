#ifndef __COMMANDTREE_H
#define __COMMANDTREE_H

#include "../Common.h"

const int PTRS_SIZE = 5;

struct Node {
    std::string data;

    Node* ptrs[PTRS_SIZE];

    // idx 0 == Node* paint;
    // idx 1 == Node* north;
    // idx 2 == Node* south;
    // idx 3 == Node* east;
    // idx 4 == Node* west;

    Node* getLastNonNull() const;
    bool isNullFromTo(int fromIdx, int toIdx) const;
};

class CommandTree {
    Node* root;

    void printRec(const std::string& prefix, Node* root, bool isLast) const;
    void doDelete(Node* root);

public:
    CommandTree();

    // We don't really need the "big 4", because the use of this class is hidden!

    void loadCommandPath(std::vector<Command> commands, int leapIndex);

    void print() const;

    ~CommandTree();
};

#endif