#include "path.hpp"

#include <cassert>
#include <vector>

Path::Path(size_t length, size_t starting_row):
    length_{length},
    starting_row_{starting_row},
    path_{std::vector<size_t>(length)} {}

// GETTER
size_t Path::length() const { return length_; }
size_t Path::starting_row() const { return starting_row_; }
unsigned int Path::ele_change() const { return ele_change_; }
const std::vector<size_t>& Path::path() const { return path_; }
// MUTATOR
void Path::set_loc(size_t col, size_t row) { path_.at(col) = row; }
void Path::inc_ele_change(unsigned int value) {
  assert(value >= 0);
  ele_change_ += value;
}