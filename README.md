# Final-Project

Name: Elvis Chen

## Description
This lab demonstrates how `shared_ptr` and `weak_ptr` behave in a circular linked list.

The SERVER builds and owns a circular linked list using `shared_ptr`. Each node also stores a `weak_ptr` to the next node so the CLIENT can try to access the list without owning it. After the SERVER deletes the list, the CLIENT tries to access it again. Because the `weak_ptr` objects do not keep nodes alive, the CLIENT can detect that the list is gone.

## Files
- `Node.h` - Defines the `Node` struct.
- `LinkedList.h` - Declares the `LinkedList` class.
- `LinkedList.cpp` - Implements the SERVER and CLIENT functions.
- `main.cpp` - Runs the lab steps in order.

## How to Compile
Use:

```bash
g++ -std=c++17 main.cpp LinkedList.cpp -o weak_ptr_lab
```

## How to Run
Use:

```bash
./weak_ptr_lab
```

## Program Steps
1. SERVER builds a circular linked list.
2. SERVER prints the linked list using `shared_ptr`.
3. CLIENT prints the linked list using `weak_ptr`.
4. SERVER deletes the circular linked list by resetting the `shared_ptr` links.
5. CLIENT tries to print again, but the list is no longer available.

## Important Idea
A `weak_ptr` can point to an object managed by a `shared_ptr`, but it does not increase the object's reference count. To use a `weak_ptr`, the program must call `.lock()` to try to get a temporary `shared_ptr`. If `.lock()` fails, that means the original object has already been deleted.
