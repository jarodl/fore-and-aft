#include "Board.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/Extensions/SimpleStringExtensions.h"

TEST_GROUP(Board)
{
  Board* board;

  void setup()
  {
    int boardWidth = 5;
    int boardHeight = 5;
    board = new Board();
  }

  void teardown()
  {
    delete board;
  }
};
