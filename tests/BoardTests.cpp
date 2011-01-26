#include "Board.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/Extensions/SimpleStringExtensions.h"

TEST_GROUP(Board)
{
  Board* example;

  void setup()
  {
    example = new Board();
  }

  void teardown()
  {
    delete example;
  }
};

//TEST(Board, sensibleNameForTest)
//{
  ////CHECK_EQUAL(0, example->DoSomething(""));
//}

