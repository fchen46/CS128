#ifndef CHARPOSITIONS_HPP
#define CHARPOSITIONS_HPP

#include <cstddef>
#include <iostream>

struct CharPositions {
  char character;
  size_t row;
  size_t col;
};

std::ostream& operator<<(std::ostream& os, const CharPositions& cp);

#endif