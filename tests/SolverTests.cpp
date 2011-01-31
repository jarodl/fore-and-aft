#include "Solver.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/Extensions/SimpleStringExtensions.h"

TEST_GROUP(Solver)
{
  Solver* solver;
  Board* testBoard;

  void setup()
  {
    testBoard = new Board(5, 5);
    solver = new Solver(*testBoard);
  }

  void teardown()
  {
    delete solver;
    delete testBoard;
  }
};
