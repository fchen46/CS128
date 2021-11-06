#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include <vector>

// Your function declarations should go in this header file
bool contains(std::vector<char> hawaiian, char input);
bool checkWord(std::string word);
std::vector<char> toVec(std::string word);
std::string toStr(std::vector<char> chars);
std::string toHawaiian(std::string word);

#endif