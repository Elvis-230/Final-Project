#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <memory>
#include <string>

struct Node {
    std::string name;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> weakNext;

    Node(const std::string& nodeName) : name(nodeName) {}

    ~Node() {
        std::cout << "Node [" << name << "] destructor" << std::endl;
    }
};

#endif