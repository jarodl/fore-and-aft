/*
 * =====================================================================================
 *
 *       Filename:  GraphTests.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/28/2011 21:53:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jarod Luebbert (), jarodluebbert@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "Graph.h"
#include "CppUTest/TestHarness.h"

TEST_GROUP(InitGraph)
{
  Graph<int> *g;

  void setup()
  {
    g = new Graph<int>();
  }

  void teardown()
  {
    delete g;
  }
};

TEST(InitGraph, testAddingNodes)
{
  //g->addNeighborToNode("ten", 10, "five", 5);
}
