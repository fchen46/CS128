#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>
#include <vector>

#include "node.hpp"

enum class Order { kASC, kDESC };

class CircularLinkedList {
public:
  CircularLinkedList();
  CircularLinkedList(const CircularLinkedList& source);
  CircularLinkedList& operator=(const CircularLinkedList& source);

  ~CircularLinkedList();
  void Clear();
  void InsertInOrder(int data);
  void Reverse();

  // helper
  void ToggleOrder();
  std::vector<Node*> ToVector();

  // print
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList& cll);

private:
  Node* head_;
  Node* tail_;
  Order node_order_;
};

// Declarations for non-member helper function
std::ostream& operator<<(std::ostream& os, const CircularLinkedList& cll);

#endif