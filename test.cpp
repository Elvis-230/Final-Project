#include "LinkedList.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

bool contains(const std::string& text, const std::string& target) {
    return text.find(target) != std::string::npos;
}

std::string captureServerPrint(LinkedList& list) {
    std::ostringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    list.SERVER_printLinkedList();
    std::cout.rdbuf(oldCout);
    return buffer.str();
}

std::string captureClientPrint(LinkedList& list) {
    std::ostringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    list.CLIENT_printLinkedList();
    std::cout.rdbuf(oldCout);
    return buffer.str();
}

std::string captureDelete(LinkedList& list) {
    std::ostringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    list.SERVER_deleteCircularLinkedList();
    std::cout.rdbuf(oldCout);
    return buffer.str();
}

void testServerPrintsAllNodes() {
    LinkedList list;
    list.SERVER_buildCircularLinkedList();

    std::string output = captureServerPrint(list);

    assert(contains(output, "Server (step 2):"));
    assert(contains(output, "[zero]"));
    assert(contains(output, "[one]"));
    assert(contains(output, "[two]"));
    assert(contains(output, "[three]"));
    assert(contains(output, "[four]"));
    assert(contains(output, "[five]"));
    assert(contains(output, "next (from shared_ptr):"));

    list.SERVER_deleteCircularLinkedList();
}

void testClientCanPrintBeforeDelete() {
    LinkedList list;
    list.SERVER_buildCircularLinkedList();

    std::string output = captureClientPrint(list);

    assert(contains(output, "Client:"));
    assert(contains(output, "[zero]"));
    assert(contains(output, "[five]"));
    assert(contains(output, "next (from weak_ptr):"));
    assert(!contains(output, "[Nothing]"));

    list.SERVER_deleteCircularLinkedList();
}

void testDeleteDestroysNodes() {
    LinkedList list;
    list.SERVER_buildCircularLinkedList();

    std::string output = captureDelete(list);

    assert(contains(output, "Server is deleting the shared_ptrs (step 4)"));
    assert(contains(output, "Node [zero] destructor"));
    assert(contains(output, "Node [one] destructor"));
    assert(contains(output, "Node [two] destructor"));
    assert(contains(output, "Node [three] destructor"));
    assert(contains(output, "Node [four] destructor"));
    assert(contains(output, "Node [five] destructor"));
}

void testClientPrintsNothingAfterDelete() {
    LinkedList list;
    list.SERVER_buildCircularLinkedList();
    list.SERVER_deleteCircularLinkedList();

    std::string output = captureClientPrint(list);

    assert(contains(output, "Client:"));
    assert(contains(output, "[Nothing]"));
}

int main() {
    testServerPrintsAllNodes();
    testClientCanPrintBeforeDelete();
    testDeleteDestroysNodes();
    testClientPrintsNothingAfterDelete();

    std::cout << "All unit tests passed!" << std::endl;
    return 0;
}
