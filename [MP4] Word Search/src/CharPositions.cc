#include "CharPositions.hpp"

std::ostream& operator<<(std::ostream& os, const CharPositions& cp) {
  os << cp.character << '\t' << cp.row << '\t' << cp.col << '\n';
  return os;
}