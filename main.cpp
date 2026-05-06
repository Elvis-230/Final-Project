#include "LinkedList.h"
#include <iostream>

int main() {
    LinkedList list;

    list.SERVER_buildCircularLinkedList();

    list.SERVER_printLinkedList();
    std::cout << std::endl;

    std::cout << "Client (step 3):" << std::endl;
    list.CLIENT_printLinkedList();
    std::cout << std::endl;

    list.SERVER_deleteCircularLinkedList();
    std::cout << std::endl;

    std::cout << "Client after linked list deleted (step 5):" << std::endl;
    list.CLIENT_printLinkedList();

    return 0;
}
