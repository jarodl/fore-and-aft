#include "../include/Solver.h"

#include "CppUTest/TestHarness.h"
/* Include the simple string extensions if you're using std::string */
//#include "CppUTest/Extensions/SimpleStringExtensions.h"

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

