#include "cord-utilities.hpp"

#include <map>

Cord* ConcatCords(Cord* left_cord, Cord* right_cord) {
  Cord* new_cord = new Cord(left_cord, right_cord);
  if (!new_cord->IsValidCord()) {
    throw std::runtime_error("Invalid Cord");
  }
  return new_cord;
}

void ReduceCords(cs128::ReferenceList<Cord*> cords) {
  std::map<std::string, Cord*> cord_map = std::map<std::string, Cord*>();
  for (Cord*& c : cords) GetMap(cord_map, c);
  return;
}

void GetMap(std::map<std::string, Cord*>& map, Cord*& cord) {
  if (FindStrMatch(map, cord)) {
    cord = map[cord->ToString()];
    return;
  }
  if (cord->GetLeft() == nullptr && cord->GetRight() == nullptr) {
    std::pair<std::string, Cord*> new_pair = make_pair(cord->ToString(), cord);
    map.insert(new_pair);
    return;
  }
  if (cord->GetLeft() != nullptr && cord->GetRight() != nullptr) {
    std::pair<std::string, Cord*> new_pair = make_pair(cord->ToString(), cord);
    map.insert(new_pair);
    GetMap(map, cord->GetLeftRef());
    GetMap(map, cord->GetRightRef());
    return;
  }
  if (cord->GetLeft() != nullptr) {
    std::pair<std::string, Cord*> new_pair = make_pair(cord->ToString(), cord);
    map.insert(new_pair);
    GetMap(map, cord->GetLeftRef());
    return;
  }
  if (cord->GetRight() != nullptr) {
    std::pair<std::string, Cord*> new_pair = make_pair(cord->ToString(), cord);
    map.insert(new_pair);
    GetMap(map, cord->GetRightRef());
    return;
  }
  return;
}

bool IsSubStr(std::string s1, std::string s2) {
  return s1.find(s2) != std::string::npos;
}

bool FindStrMatch(std::map<std::string, Cord*>& map, Cord* cord) {
  for (auto const& pair : map) {
    if (cord->ToString() == pair.first) {
      return true;
    }
  }
  return false;
}