#include "circular-linked-list.hpp"

#include <vector>

// Default Constructor
CircularLinkedList::CircularLinkedList() {
  head_ = nullptr;
  tail_ = nullptr;
  node_order_ = Order::kASC;
}

// Destructor
CircularLinkedList::~CircularLinkedList() { Clear(); }

// Destructor helper
void CircularLinkedList::Clear() {
  if (head_ == nullptr) {
    return;
  }
  Node* current = head_;
  while (current != tail_) {
    Node* next = current->next;
    delete current;
    current = next;
  }
  delete tail_;
}

// Insert data into list, maintaining node_order_
void CircularLinkedList::InsertInOrder(int data) {
  // Initialize node toInsert
  Node* toInsert = new Node(data);  // memory leak???
  // Empty List
  if (head_ == nullptr && tail_ == nullptr) {
    head_ = toInsert;
    tail_ = toInsert;
    toInsert->next = toInsert;
    return;
  }
  // Non-Empty List
  // Ascending Order
  if (node_order_ == Order::kASC) {
    // Insert as head
    if (data <= head_->data) {
      toInsert->next = head_;
      head_ = toInsert;
      tail_->next = toInsert;
    }
    // Insert as tail
    else if (data >= tail_->data) {
      tail_->next = toInsert;
      tail_ = toInsert;
      toInsert->next = head_;
    }
    // Insert in middle
    else {
      Node* current = head_;
      while (current != tail_) {
        if (data >= current->data && data <= current->next->data) {
          Node* next = current->next;
          current->next = toInsert;
          toInsert->next = next;
          break;
        }
        current = current->next;
      }
    }
  }
  // Descending Order
  else if (node_order_ == Order::kDESC) {
    // Insert as head
    if (data >= head_->data) {
      toInsert->next = head_;
      head_ = toInsert;
      tail_->next = toInsert;
    }
    // Insert as tail
    else if (data <= tail_->data) {
      tail_->next = toInsert;
      tail_ = toInsert;
      toInsert->next = head_;
    }
    // Insert in middle
    else {
      Node* current = head_;
      while (current != tail_) {
        if (data <= current->data && data >= current->next->data) {
          Node* next = current->next;
          current->next = toInsert;
          toInsert->next = next;
          break;
        }
        current = current->next;
      }
    }
  }
}

// Reverse
void CircularLinkedList::Reverse() {
  // Empty List
  if (head_ == nullptr) {
    ToggleOrder();
    return;
  }
  // Non-Empty List
  std::vector<Node*> vec = ToVector();
  int len = (int)vec.size();
  tail_ = vec.at(0);
  head_ = vec.at(len - 1);
  tail_->next = head_;
  for (int i = len - 1; i > 0; i--) {
    Node* curr = vec.at(i);
    curr->next = vec.at(i - 1);
  }
  ToggleOrder();
}

// Reverse helper function
// Toggle node order
void CircularLinkedList::ToggleOrder() {
  if (node_order_ == Order::kDESC) {
    node_order_ = Order::kASC;
  } else if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  }
}

// Reverse helper function
// Convert current list to a vector of node pointers
std::vector<Node*> CircularLinkedList::ToVector() {
  std::vector<Node*> toReturn;
  Node* current = head_;
  while (current != tail_) {
    toReturn.push_back(current);
    current = current->next;
  }
  toReturn.push_back(tail_);
  return toReturn;
}

// Copy constructor:
// Implements a deep copy policy to initialize a CircularLinkedList object from
// a source object of the same type, ensuring no memory is leaked.
CircularLinkedList::CircularLinkedList(const CircularLinkedList& source) {
  // Empty List
  if (source.head_ == nullptr) {
    head_ = nullptr;
    tail_ = nullptr;
    node_order_ = source.node_order_;
    return;
  }
  // Non-Empty List
  std::vector<Node*> vec;
  // Hold new nodes in a node pointer vector vec
  Node* curr = source.head_;
  while (curr != source.tail_) {
    Node* newNode = new Node(curr->data);
    vec.push_back(newNode);
    curr = curr->next;
  }
  Node* tailToAdd = new Node(source.tail_->data);
  vec.push_back(tailToAdd);
  // Link all the new nodes
  int len = (int)vec.size();
  head_ = vec.at(0);
  tail_ = vec.at(len - 1);
  tail_->next = head_;
  for (int i = 0; i < len - 1; i++) {
    Node* curr = vec.at(i);
    curr->next = vec.at(i + 1);
  }

  // Set order
  node_order_ = source.node_order_;
}

// Copy assignment Operator:
// Implements a deep copy policy to assign an existing CircularLinkedList object
// the source object of the same type, ensuring no memory is leaked.
CircularLinkedList& CircularLinkedList::operator=(
    const CircularLinkedList& source) {
  // Self Assignment
  if (this == &source) {
    return *this;
  }
  Clear();
  // Empty List
  if (source.head_ == nullptr) {
    head_ = nullptr;
    tail_ = nullptr;
    node_order_ = source.node_order_;
    return *this;
  }
  // Non-Empty List
  std::vector<Node*> vec;
  // Hold new nodes in a node pointer vector vec
  Node* curr = source.head_;
  while (curr != source.tail_) {
    Node* newNode = new Node(curr->data);
    vec.push_back(newNode);
    curr = curr->next;
  }
  Node* tailToAdd = new Node(source.tail_->data);
  vec.push_back(tailToAdd);
  // Link all the new nodes
  int len = (int)vec.size();
  head_ = vec.at(0);
  tail_ = vec.at(len - 1);
  tail_->next = head_;
  for (int i = 0; i < len - 1; i++) {
    Node* curr = vec.at(i);
    curr->next = vec.at(i + 1);
  }
  // Set order
  node_order_ = source.node_order_;
  return *this;
}

// Print
std::ostream& operator<<(std::ostream& os, const CircularLinkedList& cll) {
  os << "CIRCULAR LINKED LIST" << std::endl;
  if (cll.node_order_ == Order::kASC) {
    os << "Order: Ascending"
       << "\n";
  } else if (cll.node_order_ == Order::kDESC) {
    os << "Order: Descending"
       << "\n";
  }
  if (cll.head_ == nullptr) {
    os << "empty list" << std::endl;
    return os;
  }
  os << "Head:" << cll.head_->data << ", " << cll.head_ << "\n";
  os << "Tail:" << cll.tail_->data << ", " << cll.tail_ << "\n";
  os << "Curr-Ad | Curr-Dat | Next-Ad"
     << "\n";
  Node* curr = cll.head_;
  while (curr != cll.tail_) {
    os << curr << " |  " << curr->data << "  | " << curr->next << "\n";
    curr = curr->next;
  }
  os << curr << " |  " << curr->data << "  | " << curr->next << "\n";
  return os;
}
