#ifndef NODE_HPP
#define NODE_HPP

// do not modify
struct Node {
  int data;    // NOLINT (surpress warnings about public)
  Node* next;  // NOLINT (surpress warnings about public)
  Node(int data): data(data), next(nullptr) {}
  Node(int data, Node* next): data(data), next(next) {}
};

#endif