#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  // below was minimal to get tests to actually compile and given test case to
  // fail
  for (int i = 0; i < Board::kBoardHeight; i++) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
  // b.board[0][0] = DiskType::kEmpty;
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col >= Board::kBoardWidth || col < 0) {
    throw std::runtime_error("invalid column");
  }
  if (!CheckColumnFilled(b, col)) {
    throw std::runtime_error("column filled");
  }
  for (int i = 0; i <= Board::kBoardHeight; i++) {
    if (b.board[i][col] == DiskType::kEmpty) {
      b.board[i][col] = disk;
      break;
    }
  }
}

bool CheckColumnFilled(Board& b, int col) {
  for (int i = 0; i < Board::kBoardHeight; i++) {
    if (b.board[i][col] == DiskType::kEmpty) {
      return true;
    }
  }
  return false;
}

bool CheckForWinner(Board& b, DiskType disk) {
  WinningDirection directions[] = {WinningDirection::kHorizontal,
                                   WinningDirection::kVertical,
                                   WinningDirection::kLeftDiag,
                                   WinningDirection::kRightDiag};
  for (auto wd : directions) {
    if (SearchForWinner(b, disk, wd)) {
      return true;
    }
  }
  return false;
}

bool SameFour(DiskType arr[]) {
  for (int i = 1; i < 4; i++) {
    if (arr[i] != arr[i - 1]) {
      return false;
    } else if (arr[i] == DiskType::kEmpty) {
      return false;
    }
  }
  return true;
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  // Disk Holder
  static constexpr int arrSize = 4;
  DiskType arr[arrSize] = {
      DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty};
  // Vertical Check
  if (to_check == WinningDirection::kVertical) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      for (int i = 0; i < Board::kBoardHeight; i++) {
        arr[i % 4] = b.board[i][j];
        if (SameFour(arr) && b.board[i][j] == disk) {
          return true;
        }
      }
      for (int s = 0; s < arrSize; s++) {
        arr[s] = DiskType::kEmpty;
      }
    }
  }
  // Horizontal Check
  if (to_check == WinningDirection::kHorizontal) {
    for (int i = 0; i < Board::kBoardHeight; i++) {
      for (int j = 0; j < Board::kBoardWidth; j++) {
        arr[j % 4] = b.board[i][j];
        // printing
        // for (int n = 0; n < 4; n++) {
        //   if ((arr[n]) == DiskType::kEmpty) {
        //     std::cout << 'E' << i << j << ',';
        //   } else {
        //     std::cout << 'R' << i << j << ',';
        //   }
        // }
        // std::cout << ' ' << std::endl;
        // end of printing
        if (SameFour(arr) && b.board[i][j] == disk) {
          return true;
        }
      }
      for (int s = 0; s < arrSize; s++) {
        arr[s] = DiskType::kEmpty;
      }
    }
  }
  // Right Diagonal Check
  if (to_check == WinningDirection::kRightDiag) {
    for (int i = 0; i < Board::kBoardHeight; i++) {
      for (int j = 0; j < Board::kBoardWidth; j++) {
        if (i - 3 < 0 || j - 3 > Board::kBoardWidth) {
          // std::cout << "diagonal out of bound" << std::endl;
          break;
        }
        arr[0] = b.board[i][j];
        arr[1] = b.board[i - 1][j - 1];
        arr[2] = b.board[i - 2][j - 2];
        arr[3] = b.board[i - 3][j - 3];
        if (SameFour(arr) && b.board[i][j] == disk) {
          return true;
        }
      }
      for (int s = 0; s < arrSize; s++) {
        arr[s] = DiskType::kEmpty;
      }
    }
    return false;
  }
  // Left Diagonal Check
  if (to_check == WinningDirection::kLeftDiag) {
    for (int i = 0; i < Board::kBoardHeight; i++) {
      for (int j = 0; j < Board::kBoardWidth; j++) {
        if (i - 3 < 0 || j + 3 > Board::kBoardWidth) {
          // std::cout << "diagonal out of bound" << std::endl;
          break;
        }
        arr[0] = b.board[i][j];
        arr[1] = b.board[i - 1][j + 1];
        arr[2] = b.board[i - 2][j + 2];
        arr[3] = b.board[i - 3][j + 3];
        if (SameFour(arr) && b.board[i][j] == disk) {
          return true;
        }
      }
      for (int s = 0; s < arrSize; s++) {
        arr[s] = DiskType::kEmpty;
      }
    }
    return false;
  }
  return false;
}
bool BoardLocationInBounds(int row, int col) {
  if (row >= Board::kBoardHeight || row < 0) {
    return false;
  }
  if (col >= Board::kBoardWidth || col < 0) {
    return false;
  }
  return true;
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}