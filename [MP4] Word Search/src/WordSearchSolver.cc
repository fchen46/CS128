#include "WordSearchSolver.hpp"

// CONSTRUCTOR
WordSearchSolver::WordSearchSolver(
    const std::vector<std::vector<char>>& puzzle):
    puzzle_{puzzle},
    puzzle_height_{puzzle.size()},
    puzzle_width_{puzzle[0].size()} {}

// GETTER
size_t WordSearchSolver::getHeight() const { return puzzle_height_; }
size_t WordSearchSolver::getWidth() const { return puzzle_width_; }

// SOLVER
WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  std::string holder = "";
  std::vector<CharPositions> posHolder;
  WordLocation result;
  // HORIZONTAL
  if (direction == CheckDirection::kHorizontal) {
    for (int h = 0; h < (int)puzzle_height_; h++) {
      for (int w = 0; w < (int)puzzle_width_; w++) {
        holder += puzzle_[h][w];
        CharPositions cp = {puzzle_[h][w], (size_t)h, (size_t)w};
        posHolder.push_back(cp);
        if (holder.size() == word.size() + 1) {
          holder.erase(0, 1);
          posHolder.erase(posHolder.begin());
        }
        if (holder == word) {
          result.word = holder;
          result.char_positions = posHolder;
          return result;
        }
      }
      holder = "";
      posHolder.clear();
    }
  }
  // VERTICAL
  if (direction == CheckDirection::kVertical) {
    for (int w = 0; w < (int)puzzle_width_; w++) {
      for (int h = 0; h < (int)puzzle_height_; h++) {
        holder += puzzle_[h][w];
        CharPositions cp = {puzzle_[h][w], (size_t)h, (size_t)w};
        posHolder.push_back(cp);
        if (holder.size() == word.size() + 1) {
          holder.erase(0, 1);
          posHolder.erase(posHolder.begin());
        }
        if (holder == word) {
          result.word = holder;
          result.char_positions = posHolder;
          return result;
        }
      }
      holder = "";
      posHolder.clear();
    }
  }
  // RIGHT DIAG
  if (direction == CheckDirection::kRightDiag) {
    for (int j = 0; j < (int)puzzle_width_; j++) {
      int w = j;
      int h = 0;
      do {
        // if (!LocationInBounds((size_t)h, (size_t)w)) {
        //   std::cout << (int)puzzle_width_ << std::endl;
        //   std::cout << (int)puzzle_height_ << std::endl;
        //   std::cout << "not in bound!" << (size_t)h << ", " << (size_t)w
        //             << std::endl;
        // }
        holder += puzzle_[h][w];
        CharPositions cp = {puzzle_[h][w], (size_t)h, (size_t)w};
        posHolder.push_back(cp);
        if (holder.size() == word.size() + 1) {
          holder.erase(0, 1);
          posHolder.erase(posHolder.begin());
        }
        if (holder == word) {
          result.word = holder;
          result.char_positions = posHolder;
          return result;
        }
        w++;
        h++;
      } while (w < (int)puzzle_width_ && h < (int)puzzle_height_);
      holder = "";
      posHolder.clear();
    }
    for (int i = 0; i < (int)puzzle_height_; i++) {
      int w = 0;
      int h = i;
      do {
        if (!LocationInBounds((size_t)w, (size_t)h)) {
          std::cout << "not in bound" << std::endl;
        }
        holder += puzzle_[h][w];
        CharPositions cp = {puzzle_[h][w], (size_t)h, (size_t)w};
        posHolder.push_back(cp);
        if (holder.size() == word.size() + 1) {
          holder.erase(0, 1);
          posHolder.erase(posHolder.begin());
        }
        if (holder == word) {
          result.word = holder;
          result.char_positions = posHolder;
          return result;
        }
        w++;
        h++;
      } while (w < (int)puzzle_width_ && h < (int)puzzle_height_);
      holder = "";
      posHolder.clear();
    }
  }
  // LEFT DIAG
  if (direction == CheckDirection::kLeftDiag) {
    for (int i = 0; i < (int)puzzle_width_; i++) {
      int w = i;
      int h = 0;
      do {
        holder += puzzle_[h][w];
        CharPositions cp = {puzzle_[h][w], (size_t)h, (size_t)w};
        posHolder.push_back(cp);
        if (!LocationInBounds((size_t)h, (size_t)w)) {
          std::cout << "not in bound?? " << h << "," << w << std::endl;
        }
        if (holder.size() == word.size() + 1) {
          holder.erase(0, 1);
          posHolder.erase(posHolder.begin());
        }
        if (holder == word) {
          result.word = holder;
          result.char_positions = posHolder;
          return result;
        }
        w--;
        h++;
      } while (w >= 0 && h < (int)puzzle_height_);
      holder = "";
      posHolder.clear();
    }
    for (int j = 0; j < (int)puzzle_height_; j++) {
      int w = puzzle_width_ - 1;
      int h = j;
      do {
        holder += puzzle_[h][w];
        CharPositions cp = {puzzle_[h][w], (size_t)h, (size_t)w};
        posHolder.push_back(cp);
        if (!LocationInBounds((size_t)h, (size_t)w)) {
          std::cout << "not in bound?? " << h << "," << w << std::endl;
        }
        if (holder.size() == word.size() + 1) {
          holder.erase(0, 1);
          posHolder.erase(posHolder.begin());
        }
        if (holder == word) {
          result.word = holder;
          result.char_positions = posHolder;
          return result;
        }
        w--;
        h++;
      } while (w >= 0 && h < (int)puzzle_height_);
      holder = "";
      posHolder.clear();
    }
  }
  return WordLocation{};
}

// SOLVER 2 THIS IS GOOD DON'T TOUCH!
WordLocation WordSearchSolver::FindWord(const std::string& word) {
  WordLocation result;
  CheckDirection Directions[] = {CheckDirection::kHorizontal,
                                 CheckDirection::kVertical,
                                 CheckDirection::kLeftDiag,
                                 CheckDirection::kRightDiag};
  for (CheckDirection d : Directions) {
    WordLocation ThisSearch = FindWord(word, d);
    if (!ThisSearch.char_positions.empty()) {
      result = ThisSearch;
      return result;
    }
  }
  return WordLocation{};
}

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}
