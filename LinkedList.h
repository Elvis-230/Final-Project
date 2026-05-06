#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <memory>
#include <string>
#include <vector>

class LinkedList {
private:
    std::shared_ptr<Node> root;
    std::weak_ptr<Node> clientRoot;
    int numberOfNodes;

public:
    LinkedList();

    void SERVER_buildCircularLinkedList();
    void SERVER_printLinkedList() const;
    void CLIENT_printLinkedList() const;
    void SERVER_deleteCircularLinkedList();
};

#endif
