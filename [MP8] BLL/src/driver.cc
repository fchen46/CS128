#include <iostream>

#include "branched-linked-list.hpp"

int main() {
  BLL* first = new BLL();
  first->PushBack('a');
  // first->PushBack('a');
  // first->PushBack('a');

  // std::cout << first->ToString() << std::endl;  // hi
  // std::cout << first->Size() << std::endl;      // 2

  // /////////////////////////////////////

  // BLL* second = new BLL();
  // second->PushBack('b');
  // second->PushBack('b');
  // second->PushBack('b');

  // BLL* third = new BLL();
  // third->PushBack('c');
  // third->PushBack('c');
  // third->PushBack('c');

  // // /////////////////////////////////////
  // first->Join(0, third);
  // third->Join(1, second);
  std::cout << first->ToString() << std::endl;

  // first->Join(7, third);

  // first->SetAt(8, 'n');

  BLL* fourth = new BLL(*first);
  std::cout << fourth->ToString() << std::endl;
  // std::cout << first->Size() << std::endl;      // 5

  // std::cout << first->GetAt(8) << std::endl;  //

  // std::cout << first->GetIsBLLAcyclic() << std::endl;
  // std::cout << first->GetAt(7) << std::endl;  //
  // std::cout << second->ToString() << std::endl;  // i!@
  // std::cout << second->Size() << std::endl;      // 3

  // /////////////////////////////////////

  BLL* first_clone = new BLL();
  *first_clone = *first;

  std::cout << first_clone->ToString() << std::endl;  // hii!@
  // std::cout << first_clone->Size() << std::endl; // 5

  delete first;
  delete fourth;
  delete first_clone;

  return 0;
}
