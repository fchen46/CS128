#include "branched-linked-list.hpp"

// CONSTRUCTOR
// Initializes an empty BLL
BLL::BLL() { head_ = nullptr; }

// COPY CONSTRUCTOR
BLL::BLL(const BLL& to_copy) {
  if (to_copy.head_ == nullptr) {
    head_ = nullptr;
    return;
  }
  Node* curr = to_copy.head_;
  Node* prev = nullptr;
  while (curr != nullptr) {
    Node* newNode = new Node(curr->data_);
    if (curr->next_bll_ != nullptr) {
      BLL* nextBLL = curr->next_bll_;
      BLL* newBLL = new BLL(*nextBLL);
      newNode->next_bll_ = newBLL;
    }
    if (prev == nullptr) {
      head_ = newNode;
      prev = newNode;
      curr = curr->next_node_;
    } else {
      prev->next_node_ = newNode;
      prev = newNode;
      curr = curr->next_node_;
    }
  }
  return;
}

// COPY OPERATOR
BLL& BLL::operator=(const BLL& rhs) {
  // check self-assignment
  if (this == &rhs) {
    return *this;
  }
  if (rhs.head_ == nullptr) {
    head_ = nullptr;
    return *this;
  }
  Node* curr = rhs.head_;
  Node* prev = nullptr;
  while (curr != nullptr) {
    Node* newNode = new Node(curr->data_);
    if (curr->next_bll_ != nullptr) {
      BLL* nextBLL = curr->next_bll_;
      BLL* newBLL = new BLL(*nextBLL);
      newNode->next_bll_ = newBLL;
    }
    if (prev == nullptr) {
      head_ = newNode;
      prev = newNode;
      curr = curr->next_node_;
    } else {
      prev->next_node_ = newNode;
      prev = newNode;
      curr = curr->next_node_;
    }
  }
  return *this;
}

// Creates a node and appends to the end of the current BLL’s node list
// (next_node_), and returns the pointer to it.
Node* BLL::PushBack(char dat) {
  Node* newNode = new Node(dat);
  newNode->next_node_ = nullptr;
  // Empty BLL
  if (head_ == nullptr) {
    head_ = newNode;
    return newNode;
  }
  // Non-Empty BLL
  Node* curr = head_;
  while (curr->next_node_ != nullptr) {
    curr = curr->next_node_;
  }
  curr->next_node_ = newNode;
  return newNode;
}

// Returns the data_ all concatenated into a string, starting from head_; if
// there is no data, returns the empty string.
cs128::string BLL::ToString() const {
  if (head_ == nullptr) {
    return "";
  }
  cs128::string str = "";
  Node* curr = head_;
  while (curr != nullptr) {
    str.push_back(curr->data_);
    if (curr->next_bll_ != nullptr) {
      BLL* nextBll = curr->next_bll_;
      str.append(nextBll->ToString());
    }
    curr = curr->next_node_;
  }
  return str;
}

// Returns the size of the BLL
size_t BLL::Size() const {
  cs128::string str = ToString();
  return str.length();
}

// Gets the data_ of idxth index starting from head_
// Throws an exception when idx is out of bounds
char BLL::GetAt(size_t idx) const {
  if (idx >= Size()) {
    throw "nope";
  }
  Node* n = GetNode(idx);
  return n->data_;
}

// Gets the data_ of idxth index starting from head_.
// Throws an exception when idx is out of bounds.
void BLL::SetAt(size_t idx, char dat) {
  if (idx >= Size()) {
    throw "nope";
  }
  GetNode(idx)->data_ = dat;
}

// Joins the given list to idxth index starting from head_
// Throws an exception when this Join operation would cause this BLL to be
// cyclic or there is already next_bll_.
void BLL::Join(size_t idx, BLL* list) {
  Node* toJoin = GetNode(idx);
  if (idx >= Size()) {
    throw std::runtime_error("Size out of bound");
  }
  if (toJoin->next_bll_ != nullptr) {
    throw std::runtime_error(
        "next_bll_ at this node already exist, cannot join");
  }
  toJoin->next_bll_ = list;
  if (IsBLLAcyclic() == true) {
    toJoin->next_bll_ = nullptr;
    throw std::runtime_error("Cyclic, cannot join");
  }
}

// Helper function for GetAt, SetAt, and Join, uses recursion
Node* BLL::GetNode(size_t idx) const {
  size_t index = idx;
  Node* curr = head_;
  while (curr != nullptr) {
    if (index == 0) {
      return curr;
    }
    if (curr->next_bll_ != nullptr && curr->next_bll_->Size() >= index) {
      BLL* nextBll = curr->next_bll_;
      return nextBll->GetNode(index - 1);
    }
    if (curr->next_bll_ != nullptr && curr->next_bll_->Size() < index) {
      index = index - curr->next_bll_->Size() - 1;
      curr = curr->next_node_;
      continue;
    }
    index--;
    curr = curr->next_node_;
  }
  return curr;
}

// Deallocate free store memory from head_ of this BLL and everything that it
// involves
BLL::~BLL() { Clear(); }

// Clear
void BLL::Clear() {
  Node* curr = head_;
  while (curr != nullptr) {
    Node* next = curr->next_node_;
    if (curr->next_bll_ != nullptr) {
      // curr->next_bll_->Clear();
      delete curr->next_bll_;
    }
    delete curr;
    curr = next;
  }
  head_ = nullptr;
}

// Returns true if the list is acyclic (not cyclic), and false if cyclic
bool BLL::IsBLLAcyclic() const {
  if (head_ == nullptr) {
    return false;
  }
  Node* Tortoise = head_;
  Node* Hare = GetNextNode(head_);
  while (Tortoise != nullptr && Hare != nullptr) {
    if (Tortoise == Hare) {
      return true;
    }
    Tortoise = GetNextNode(Tortoise);
    Hare = GetNextNode(GetNextNode(Hare));
  }
  return false;
}

// Helper function for IsBLLAcyclic
Node* BLL::GetNextNode(Node* curr) const {
  if (curr == nullptr) {
    return nullptr;
  }
  if (curr->next_bll_ != nullptr) {
    return curr->next_bll_->head_;
  }
  return curr->next_node_;
}

cs128::string BLL::GetIsBLLAcyclic() const {
  cs128::string str;
  str = IsBLLAcyclic() ? "true" : "false";
  return str;
}
