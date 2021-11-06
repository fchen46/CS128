#ifndef CS128_REFERENCE_LIST_HPP
#define CS128_REFERENCE_LIST_HPP

#include <functional>
#include <initializer_list>

namespace cs128 {
  template <typename T>
  using ReferenceList = std::initializer_list<std::reference_wrapper<T>>;
}  // namespace cs128
#endif