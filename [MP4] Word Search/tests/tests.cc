// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Zora Zhang                      Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
std::vector<std::vector<char>> puzzle{{'d', 'h', 'a', 'i', 'u', 'e'},
                                      {'h', 'a', 'a', 'z', 'o', 'e'},
                                      {'u', 's', 'z', 'o', 'm', 'e'},
                                      {'a', 'u', 'z', 'r', 'a', 'e'},
                                      {'t', 'o', 'z', 'o', 'u', 'e'}};
WordSearchSolver wss(puzzle);
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

// TEST_CASE("WordSearchInitialization", "[WordSearchSolver]") {
//   std::vector<std::vector<char>> puzzle{{'d', 'h', 'a', 'i', 'u', 'e'},
//                                         {'h', 'a', 'a', 'z', 'o', 'e'},
//                                         {'u', 's', 'z', 'o', 'm', 'e'},
//                                         {'a', 'u', 'z', 'r', 'a', 'e'},
//                                         {'t', 'o', 'z', 'o', 'u', 'e'}};
//   WordSearchSolver wss(puzzle);
// }

TEST_CASE("Horizontal", "[FindWord]") {
  CharPositions cp1 = {'h', 0, 1};
  CharPositions cp2 = {'a', 0, 2};
  CharPositions cp3 = {'i', 0, 3};
  std::vector<CharPositions> charPos = {cp1, cp2, cp3};
  std::string solution = "hai";
  WordLocation horizResult = wss.FindWord("hai", CheckDirection::kHorizontal);
  WordLocation vertiResult = wss.FindWord("hai", CheckDirection::kVertical);
  WordLocation otherFind = wss.FindWord("hai");
  SECTION("Position matches") {
    for (int i = 0; i < (int)horizResult.char_positions.size(); i++) {
      REQUIRE(horizResult.char_positions[i].col == charPos[i].col);
      REQUIRE(horizResult.char_positions[i].row == charPos[i].row);
    }
  }
  SECTION("Word matches") {
    REQUIRE(otherFind.word == solution);
    REQUIRE(horizResult.word == solution);
    REQUIRE_FALSE(horizResult.word == " ");
    REQUIRE_FALSE(vertiResult.word == solution);
  }
}

TEST_CASE("Vertical", "[FindWord]") {
  CharPositions cp1 = {'o', 2, 3};
  CharPositions cp2 = {'r', 3, 3};
  CharPositions cp3 = {'o', 4, 3};
  std::vector<CharPositions> charPos = {cp1, cp2, cp3};
  std::string solution = "oro";
  WordLocation vertiResult = wss.FindWord("oro", CheckDirection::kVertical);
  WordLocation horizResult = wss.FindWord("oro", CheckDirection::kHorizontal);
  WordLocation otherFind = wss.FindWord("oro");
  SECTION("Position matches") {
    for (int i = 0; i < (int)vertiResult.char_positions.size(); i++) {
      REQUIRE(vertiResult.char_positions[i].col == charPos[i].col);
      REQUIRE(vertiResult.char_positions[i].row == charPos[i].row);
    }
  }
  SECTION("Word matches") {
    REQUIRE(otherFind.word == solution);
    REQUIRE(vertiResult.word == solution);
    REQUIRE_FALSE(vertiResult.word == " ");
    REQUIRE_FALSE(horizResult.word == solution);
  }
}

TEST_CASE("Left Diagonal", "FindWord") {
  CharPositions cp1 = {'u', 0, 4};
  CharPositions cp2 = {'z', 1, 3};
  CharPositions cp3 = {'z', 2, 2};
  std::vector<CharPositions> charPos = {cp1, cp2, cp3};
  std::string solution = "uzz";
  WordLocation leftdiagResult = wss.FindWord("uzz", CheckDirection::kLeftDiag);
  WordLocation horizResult = wss.FindWord("uzz", CheckDirection::kHorizontal);
  WordLocation otherFind = wss.FindWord("uzz");
  SECTION("Position matches") {
    for (int i = 0; i < (int)leftdiagResult.char_positions.size(); i++) {
      REQUIRE(leftdiagResult.char_positions[i].col == charPos[i].col);
      REQUIRE(leftdiagResult.char_positions[i].row == charPos[i].row);
    }
  }
  SECTION("Word matches") {
    REQUIRE(otherFind.word == solution);
    REQUIRE(leftdiagResult.word == solution);
    REQUIRE_FALSE(leftdiagResult.word == " ");
    REQUIRE_FALSE(horizResult.word == solution);
  }
}

TEST_CASE("Right Diagonal", "FindWord") {
  CharPositions cp1 = {'a', 0, 2};
  CharPositions cp2 = {'z', 1, 3};
  CharPositions cp3 = {'m', 2, 4};
  std::vector<CharPositions> charPos = {cp1, cp2, cp3};
  std::string solution = "azm";
  WordLocation rightdiagResult =
      wss.FindWord("azm", CheckDirection::kRightDiag);
  WordLocation leftdiagResult = wss.FindWord("azm", CheckDirection::kLeftDiag);
  WordLocation otherFind = wss.FindWord("azm");
  SECTION("Position matches") {
    for (int i = 0; i < (int)rightdiagResult.char_positions.size(); i++) {
      REQUIRE(rightdiagResult.char_positions[i].col == charPos[i].col);
      REQUIRE(rightdiagResult.char_positions[i].row == charPos[i].row);
    }
  }
  SECTION("Word matches") {
    REQUIRE(otherFind.word == solution);
    REQUIRE(rightdiagResult.word == solution);
    REQUIRE_FALSE(rightdiagResult.word == " ");
    REQUIRE_FALSE(leftdiagResult.word == solution);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////