#ifndef NODE_HPP
#define NODE_HPP

// This is called forward declaration.
class BLL;
// Do not erase.

// Definition of node provided to you
struct Node {
  Node() = default;
  Node(char value) : data_(value) {}

  char data_ = '\0';
  Node* next_node_ = nullptr;
  BLL* next_bll_ = nullptr;
};

#endif