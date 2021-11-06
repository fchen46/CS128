#ifndef WORDLOCATION_HPP
#define WORDLOCATION_HPP

#include <iostream>
#include <string>
#include <vector>

#include "CharPositions.hpp"

struct WordLocation {
  std::string word;
  std::vector<CharPositions> char_positions;
};

std::ostream& operator<<(std::ostream& os, const WordLocation& wl);

#endif