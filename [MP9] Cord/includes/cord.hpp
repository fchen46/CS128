#ifndef CORD_HPP
#define CORD_HPP

#include <cstddef>
#include <map>
#include <stdexcept>
#include <string>

#include "cs128referencelist.hpp"

class Cord {
public:
  Cord(std::string dat);
  Cord(Cord* left_cord, Cord* right_cord);

  ~Cord() = default;
  Cord(const Cord&) = delete;
  Cord& operator=(const Cord&) = delete;

  // Getters
  size_t Length() const;
  const std::string& GetData() const;
  Cord* GetLeft() const;
  Cord* GetRight() const;
  Cord*& GetLeftRef();
  Cord*& GetRightRef();

  // Cord Operations
  std::string ToString() const;
  // lower inclusive, upper exclusive
  Cord* SubString(size_t lower_idx, size_t upper_idx);
  char At(size_t idx) const;

  // Friend functions
  friend Cord* ConcatCords(Cord* left_cord, Cord* right_cord);
  friend void ReduceCords(cs128::ReferenceList<Cord*> cords);

  // Helper functions
  std::string GetString(size_t lower_idx, size_t upper_idx);

private:
  Cord* left_ = nullptr;
  Cord* right_ = nullptr;
  size_t length_;
  std::string data_;

  bool IsValidCord() const;
};

#endif
