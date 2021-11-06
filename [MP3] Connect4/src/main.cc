#include <iostream>

#include "board.hpp"

int main() {
  // Board b;  // NOLINT
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  std::cout << BoardToStr(b) << std::endl;
  std::cout << SearchForWinner(
                   b, DiskType::kPlayer2, WinningDirection::kRightDiag)
            << std::endl;
}