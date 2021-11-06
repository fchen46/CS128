#include <iostream>
#include <string>

#include "functions.hpp"

int main(int argc, char** argv) {
  // pre-processing of arguments
  if (argc != 2) {
    std::cerr << "Usage: ./bin/exec word" << std::endl;
    return 1;
  }
  std::string word = argv[1];
  if (!checkWord(word)) {
    std::cout << word
              << " contains a character not a part of the Hawaiian language."
              << std::endl;
    return 1;
  }

  // process hawaiian words
  std::string phonetics = toHawaiian(word);
  std::cout << phonetics << std::endl;
  return 666;
}