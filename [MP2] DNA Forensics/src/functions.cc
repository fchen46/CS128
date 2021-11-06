#include "functions.hpp"

#include <fstream>

#include "utilities.hpp"

int countSingleSTR(std::string DNA, std::string STR) {
  int DNALen = (int)DNA.length();
  int STRLen = (int)STR.length();
  int max = 0;
  int counter = 0;
  for (int i = 0; i < DNALen; i++) {
    std::string holder = "";
    for (int j = 0; j < STRLen; j++) {
      holder += DNA[i + j];
    }
    if (holder == STR) {
      counter += 1;
      i += STRLen - 1;
    } else {
      if (counter > max) {
        max = counter;
        counter = 0;
      }
    }
  }
  if (counter > max) {
    max = counter;
  }
  return max;
}

std::map<std::string, int> countSTR(std::string DNA,
                                    std::vector<std::string> STR) {
  // initiate the map
  std::map<std::string, int> toReturn;
  for (std::string x : STR) {
    int count = countSingleSTR(DNA, x);
    toReturn.insert(std::pair<std::string, int>(x, count));
  }
  return toReturn;
}

std::vector<std::string> getSTR(std::string file) {
  std::ifstream ifs{file};
  std::vector<std::string> header;
  std::vector<std::string> toReturn;
  int counter = 0;
  for (std::string line; std::getline(ifs, line); line = "") {
    counter += 1;
    if (counter == 1) {
      header = utilities::get_substrs(line, ',');
    }
  }
  for (int i = 0; i < (int)header.size(); i++) {
    if (i != 0) {
      toReturn.push_back(header[i]);
    }
  }
  return toReturn;
}

std::map<std::string, std::map<std::string, int>> getPeople(std::string file) {
  std::vector<std::string> STRs = getSTR(file);
  // int STRnum = (int)STRs.size();
  std::ifstream ifs{file};
  std::map<std::string, std::map<std::string, int>> toReturn;
  std::vector<std::string> holder;
  int counter = 0;
  for (std::string line; std::getline(ifs, line); line = "") {
    counter += 1;
    if (counter != 1) {
      // process each line of person info
      holder = utilities::get_substrs(line, ',');
      std::string name = holder[0];
      std::map<std::string, int> STRcount;
      for (int i = 0; i < (int)holder.size(); i++) {
        if (i == 1) {
          STRcount.insert(
              std::pair<std::string, int>(STRs[0], stoi(holder[1])));
        } else if (i == 2) {
          STRcount.insert(
              std::pair<std::string, int>(STRs[1], stoi(holder[2])));
        } else {
          STRcount.insert(
              std::pair<std::string, int>(STRs[2], stoi(holder[3])));
        }
      }
      toReturn.insert(
          std::pair<std::string, std::map<std::string, int>>(name, STRcount));
    }
  }
  return toReturn;
}

bool matchSTR(std::map<std::string, int> STRmap,
              std::map<std::string, int> person) {
  for (auto STR : STRmap) {
    if (person[STR.first] != STR.second) {
      return false;
    }
  }
  return true;
}

std::string search(std::map<std::string, int> STRmap,
                   std::map<std::string, std::map<std::string, int>> people) {
  for (auto person : people) {
    if (matchSTR(STRmap, person.second)) {
      return person.first;
    }
  }
  return "No match";
}