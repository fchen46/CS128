#ifndef BRANCHED_LINKED_LIST_HPP
#define BRANCHED_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>

#include "cs128string.hpp"
#include "node.hpp"

class BLL {
public:
  BLL();                    // done
  BLL(const BLL& to_copy);  // in progress
  ~BLL();                   // in progress

  BLL& operator=(const BLL& rhs);    // in progress
  Node* PushBack(char dat);          // done
  char GetAt(size_t idx) const;      // done
  void SetAt(size_t idx, char dat);  // done
  void Join(size_t idx,
            BLL* list);            // done
  cs128::string ToString() const;  // done
  size_t Size() const;             // done

  // Helper Functions
  Node* GetNode(size_t idx) const;        // done
  void Clear();                           // in progress
  cs128::string GetIsBLLAcyclic() const;  // done
  Node* GetNextNode(Node* curr) const;    // done

private:
  Node* head_;
  bool IsBLLAcyclic() const;  // done
};

#endif
