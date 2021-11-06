#ifndef CORD_UTILITIES_HPP
#define CORD_UTILITIES_HPP

#include "cord.hpp"

Cord* ConcatCords(Cord* left_cord, Cord* right_cord);
void ReduceCords(cs128::ReferenceList<Cord*> cords);

// ReduceCords Helpers
void GetMap(std::map<std::string, Cord*>& map, Cord*& cord);
bool IsSubStr(std::string s1, std::string s2);
bool FindStrMatch(std::map<std::string, Cord*>& map, Cord* cord);

#endif
