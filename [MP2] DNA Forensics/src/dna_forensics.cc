#include <iostream>

#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }

  std::string file = argv[1];
  std::string DNA = argv[2];

  std::map<std::string, int> STRmap = countSTR(DNA, getSTR(file));
  std::map<std::string, std::map<std::string, int>> people = getPeople(file);

  std::cout << search(STRmap, people) << std::endl;

  return 0;
}