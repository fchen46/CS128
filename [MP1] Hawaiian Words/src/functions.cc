#include "functions.hpp"

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

// Your function definitions should go in this source file.

// checkWord helper function
bool contains(std::vector<char> hawaiian, char input) {
  for (char c : hawaiian) {
    if (input == c) {
      return true;
    }
  }
  return false;
}

// Check if a word contain any character that is not a part of the Hawaiian
// language
bool checkWord(std::string word) {
  std::vector<char> hawaiian = {
      'a', 'e', 'i', 'o', 'u', 'p', 'k', 'h', 'l', 'm', 'n', 'w', ' ', '\''};
  for (char x : word) {
    if (!contains(hawaiian, tolower(x))) {
      return false;
    }
  }
  return true;
}

// Convert string to a char vector
std::vector<char> toVec(std::string word) {
  std::vector<char> toReturn;
  for (char c : word) {
    toReturn.push_back(tolower(c));
  }
  return toReturn;
}

// Convert char vector to string
std::string toStr(std::vector<char> chars) {
  std::string toReturn = "";
  for (char c : chars) {
    toReturn += c;
  }
  return toReturn;
}

// Convert to Hawaiian
std::string toHawaiian(std::string word) {
  std::vector<char> chars = toVec(word);
  std::string toReturn;
  std::vector<char> consonants = {'p', 'k', 'h', 'l', 'm', 'n'};
  std::vector<char> vowels = {'a', 'e', 'i', 'o', 'u'};
  for (int i = 0; i < (int)chars.size(); i++) {
    // space
    if (chars[i] == ' ') {
      if (toReturn.back() == '-') {
        toReturn.pop_back();
      }
      toReturn += ' ';
    }
    // apostrophe
    else if (chars[i] == '\'') {
      if (toReturn.back() == '-') {
        toReturn.pop_back();
      }
      toReturn += chars[i];
    }
    // consonants
    else if (contains(consonants, chars[i])) {
      toReturn += chars[i];
    }
    // w
    else if (chars[i] == 'w') {
      if (i == 0) {
        toReturn += 'w';
      } else if (chars[i - 1] == 'a' || chars[i - 1] == 'u' ||
                 chars[i - 1] == 'o') {
        toReturn += 'w';
      } else if (chars[i - 1] == 'i' || chars[i - 1] == 'e') {
        toReturn += 'v';
      }
    }
    // vowel groups
    // else if ((i != (int)chars.size() - 1) && contains(vowels, chars[i + 1]))
    // {
    else if ((i != (int)chars.size() - 1) &&
             (chars[i] == 'a' && chars[i + 1] == 'i')) {
      toReturn += "eye-";
      i += 1;
    } else if ((i != (int)chars.size() - 1) &&
               (chars[i] == 'a' && chars[i + 1] == 'e')) {
      toReturn += "eye-";
      i += 1;
    } else if ((i != (int)chars.size() - 1) &&
               (chars[i] == 'a' && chars[i + 1] == 'o')) {
      toReturn += "ow-";
      i += 1;
    } else if ((i != (int)chars.size() - 1) &&
               (chars[i] == 'a' && chars[i + 1] == 'u')) {
      toReturn += "ow-";
      i += 1;
    } else if ((i != (int)chars.size() - 1) &&
               (chars[i] == 'e' && chars[i + 1] == 'i')) {
      toReturn += "ay-";
      i += 1;
    } else if ((i != (int)chars.size() - 1) &&
               (chars[i] == 'e' && chars[i + 1] == 'u')) {
      toReturn += "eh-oo-";
      i += 1;
    } else if ((i != (int)chars.size() - 1) &&
               (chars[i] == 'o' && chars[i + 1] == 'i')) {
      toReturn += "oy-";
      i += 1;
    } else if ((i != (int)chars.size() - 1) &&
               (chars[i] == 'o' && chars[i + 1] == 'u')) {
      toReturn += "ow-";
      i += 1;
    } else if ((i != (int)chars.size() - 1) &&
               (chars[i] == 'u' && chars[i + 1] == 'i')) {
      toReturn += "ooey-";
      i += 1;
    }
    // }
    // vowels
    // else {
    else if (chars[i] == 'a') {
      toReturn += "ah-";
    } else if (chars[i] == 'e') {
      toReturn += "eh-";
    } else if (chars[i] == 'i') {
      toReturn += "ee-";
    } else if (chars[i] == 'o') {
      toReturn += "oh-";
    } else if (chars[i] == 'u') {
      toReturn += "oo-";
    }
  }
  // }
  if (toReturn.back() == '-') {
    toReturn.pop_back();
  }
  return toReturn;
}