#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() : root(nullptr), numberOfNodes(0) {}

void LinkedList::SERVER_buildCircularLinkedList() {
    std::vector<std::string> names = {"zero", "one", "two", "three", "four", "five"};
    numberOfNodes = static_cast<int>(names.size());

    root = std::make_shared<Node>(names[0]);
    clientRoot = root;

    std::shared_ptr<Node> node = root;

    for (int i = 1; i < numberOfNodes; i++) {
        node->next = std::make_shared<Node>(names[i]);
        node->weakNext = node->next;
        node = node->next;
    }

    node->next = root;
    node->weakNext = root;
}

void LinkedList::SERVER_printLinkedList() const {
    std::cout << "Server (step 2):" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    if (!root) {
        std::cout << "[Nothing]" << std::endl;
        return;
    }

    std::shared_ptr<Node> current = root;

    for (int i = 0; i < numberOfNodes; i++) {
        std::cout << "[" << current->name << "] : "
                  << "use_count: " << current.use_count()
                  << " address: " << current.get()
                  << " next (from shared_ptr): " << current->next.get()
                  << std::endl;

        current = current->next;
    }
}

void LinkedList::CLIENT_printLinkedList() const {
    std::cout << "Client:" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    std::shared_ptr<Node> current = clientRoot.lock();

    if (!current) {
        std::cout << "[Nothing]" << std::endl;
        return;
    }

    for (int i = 0; i < numberOfNodes; i++) {
        std::shared_ptr<Node> nextNode = current->weakNext.lock();

        std::cout << "[" << current->name << "] : "
                  << "use_count: " << current.use_count()
                  << " address: " << current.get()
                  << " next (from weak_ptr): " << nextNode.get()
                  << std::endl;

        if (!nextNode) {
            std::cout << "Yipes! shared_ptr not available" << std::endl;
            return;
        }

        current = nextNode;
    }
}

void LinkedList::SERVER_deleteCircularLinkedList() {
    std::cout << "Server is deleting the shared_ptrs (step 4)" << std::endl;

    if (!root) {
        return;
    }

    std::shared_ptr<Node> current = root;

    for (int i = 0; i < numberOfNodes; i++) {
        std::shared_ptr<Node> nextNode = current->next;
        current->next.reset();
        current = nextNode;
    }

    root.reset();
}
