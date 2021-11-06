#include <iostream>
#include <string>
#include <vector>

#include "WordSearchSolver.hpp"

int main() {
  std::vector<std::vector<char>> puzzle{{'d', 'h', 'a', 'i', 'u', 'e'},
                                        {'h', 'a', 'a', 'z', 'o', 'e'},
                                        {'u', 's', 'z', 'o', 'm', 'e'},
                                        {'a', 'u', 'z', 'r', 'a', 'e'},
                                        {'t', 'o', 'z', 'o', 'u', 'e'}};
  WordSearchSolver wss(puzzle);
  // std::cout << wss.getHeight() << std::endl;
  std::cout << wss.FindWord("dazr", CheckDirection::kRightDiag);
  std::cout << wss.FindWord("eoozo");
}