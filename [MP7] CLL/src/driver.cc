#include <iostream>

#include "circular-linked-list.hpp"

int main() {
  CircularLinkedList cll;
  cll.InsertInOrder(10);
  // cll.InsertInOrder(1);
  // cll.InsertInOrder(3);
  cll.InsertInOrder(4);
  cll.InsertInOrder(1);
  // cll.InsertInOrder(5);
  // cll.InsertInOrder(19);
  // cll.InsertInOrder(12);
  std::cout << cll << std::endl;
  // cll.InsertInOrder(13);
  // cll.InsertInOrder(11);
  // cll.InsertInOrder(14);
  // cll.Reverse();
  // std::cout << cll << std::endl;
  // cll.Reverse();
  // std::cout << cll << std::endl;

  // std::cout << std::endl << "cll2" << std::endl;
  // CircularLinkedList cll2(cll);
  // std::cout << cll2 << std::endl;
  // cll2.Reverse();
  // std::cout << cll2 << std::endl;
  // cll2.Reverse();
  // std::cout << cll2 << std::endl;

  // std::cout << std::endl << "cll3" << std::endl;
  // CircularLinkedList cll3;
  // cll3.InsertInOrder(3);
  // cll3 = cll;
  // std::cout << cll3 << std::endl;
  // cll3.Reverse();
  // std::cout << cll3 << std::endl;
}
