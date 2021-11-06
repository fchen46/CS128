#ifndef PATH_H
#define PATH_H

#include <cstdlib>  // for size_t
#include <vector>

class Path {
public:
  // CONSTRUCTOR
  Path(size_t length, size_t starting_row);
  // GETTERS
  size_t length() const;
  size_t starting_row() const;
  unsigned int ele_change() const;
  const std::vector<size_t>& path() const;
  // MUTATOR
  void inc_ele_change(unsigned int value);
  void set_loc(size_t col, size_t row);

private:
  size_t length_;
  size_t starting_row_;
  std::vector<size_t> path_;
  unsigned int ele_change_ = 0;
};

#endif