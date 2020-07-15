#include "CommandTree.h"
#include <iomanip>

bool Node::isNullFromTo(int fromIdx, int toIdx) const {
    int counter = 0;
    for (int i = fromIdx; i <= toIdx; i++) {
        if (ptrs[i] == nullptr) {
            counter++;
        }
    }
    return counter == toIdx + 1 - fromIdx;
}

Node* Node::getLastNonNull() const {
    bool paintIsLast = isNullFromTo(1, 4);
    bool northIsLast = isNullFromTo(2, 4);
    bool southIsLast = isNullFromTo(3,4);
    bool eastIsLast =  isNullFromTo(4,4);

    std::vector<bool> returns;
    returns.push_back(paintIsLast);
    returns.push_back(northIsLast);
    returns.push_back(southIsLast);
    returns.push_back(eastIsLast);
    returns.push_back(true);

    for (int i = 0; i < returns.size(); i++) {
        if (returns[i]) {
            return ptrs[i];
        }
    }
}

CommandTree::CommandTree() {
    root = new Node{"[ START ]",
                    nullptr,
                    nullptr,
                    nullptr,
                    nullptr,
                    nullptr };
}

void loadCommandBoxes(std::map<std::string, int>& commandBoxes) {
    commandBoxes.insert({"[ P ]", 0});
    commandBoxes.insert({"[ N ]", 1});
    commandBoxes.insert({"[ S ]", 2});
    commandBoxes.insert({"[ E ]", 3});
    commandBoxes.insert({"[ W ]", 4});
}

void CommandTree::loadCommandPath(std::vector<Command> commands, int leapIndex) {
    Node* currRoot = root;

    std::map<std::string, int> commandBoxes;
    loadCommandBoxes(commandBoxes);

    for (int i = 0; i < commands.size(); i++) {
        if (currRoot->ptrs[commandBoxes[commands[i]]] == nullptr) {
            currRoot->ptrs[commandBoxes[commands[i]]] = new Node{commands[i],
                                                                 nullptr,
                                                                 nullptr,
                                                                 nullptr,
                                                                 nullptr,
                                                                 nullptr};
        }
        currRoot = currRoot->ptrs[commandBoxes[commands[i]]];

        if (i + 1 == commands.size()) { // last element
            currRoot->data = currRoot->data + "  (" + std::to_string(leapIndex) + ")";
        } // Just appending the leap index after the last element
    }
}

void CommandTree::printRec(const std::string& prefix, Node* root, bool isLast) const {
    if(root != nullptr) {
        if (root->data == "[ START ]") {
            std::cout << "  " << root->data << std::endl;
        } else {
            std::cout << prefix << (isLast ? "'---> " : "|---> ") << root->data << std::endl;
        }
        for (Node* & ptr : root->ptrs) {
            printRec(prefix + (isLast ? "        " : "|       " ), ptr, ptr == root->getLastNonNull());
        }
    }
}

void CommandTree::print() const {
    printRec("", root, true);
}

void CommandTree::doDelete(Node* root) {
    if (root == nullptr) {
        return;
    }
    for (Node* & ptr : root->ptrs) {
        doDelete(ptr);
    }
    delete root;
}

CommandTree::~CommandTree() {
    doDelete(root);
}