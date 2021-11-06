#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <map>
#include <vector>

#include "utilities.hpp"

// extract STRs from csv file
std::vector<std::string> getSTR(std::string file);
// count consecutive appearance of a single STR in the DNA string
int countSingleSTR(std::string DNA, std::string STR);
// store counts of STR in a map
std::map<std::string, int> countSTR(std::string DNA,
                                    std::vector<std::string> STR);
// store each person with their STR info
std::map<std::string, std::map<std::string, int>> getPeople(std::string file);
// compare the target STR numbers with a person's STR info
bool matchSTR(std::map<std::string, int> STRmap,
              std::map<std::string, int> person);
// search all people for matching STR
std::string search(std::map<std::string, int> STRmap,
                   std::map<std::string, std::map<std::string, int>> people);

#endif