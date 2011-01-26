#include "Solver.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/Extensions/SimpleStringExtensions.h"

TEST_GROUP(Solver)
{
  Solver* example;

  void setup()
  {
    example = new Solver();
  }

  void teardown()
  {
    delete example;
  }
};

//TEST(Solver, sensibleNameForTest)
//{
  ////CHECK_EQUAL(0, example->DoSomething(""));
//}

