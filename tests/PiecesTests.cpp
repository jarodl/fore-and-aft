/*
 * =====================================================================================
 *
 *       Filename:  PiecesTests.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/26/2011 10:32:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jarod Luebbert (), jarodluebbert@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "Pieces.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/Extensions/SimpleStringExtensions.h"

TEST_GROUP(Pieces)
{
  Pieces* fiveByFive;
  Pieces* sevBySev;
  Pieces* ninByNin;

  void setup()
  {
    fiveByFive = new Pieces(5, 5);
    sevBySev = new Pieces(7, 7);
    ninByNin = new Pieces(9, 9);
  }

  void teardown()
  {
    delete fiveByFive;
    delete sevBySev;
    delete ninByNin;
  }
};

TEST(Pieces, testPiecesStringSize)
{
  CHECK_EQUAL(17, fiveByFive->getSize());
  CHECK_EQUAL(31, sevBySev->getSize());
  CHECK_EQUAL(49, ninByNin->getSize());
}

TEST(Pieces, testPiecesClearsValues)
{
  char fiveExpected[] = "RRRRRRRR_BBBBBBBB";
  STRCMP_EQUAL(fiveExpected, fiveByFive->getValues().c_str());
  char sevExpected[] = "RRRRRRRRRRRRRRR_BBBBBBBBBBBBBBB";
  STRCMP_EQUAL(sevExpected, sevBySev->getValues().c_str());
  char ninExpected[] = "RRRRRRRRRRRRRRRRRRRRRRRR_BBBBBBBBBBBBBBBBBBBBBBBB";
  STRCMP_EQUAL(ninExpected, ninByNin->getValues().c_str());
}

TEST(Pieces, testPiecesMovesDoNotExist)
{
  CHECK_EQUAL(false, fiveByFive->movesExist());
  CHECK_EQUAL(false, sevBySev->movesExist());
  CHECK_EQUAL(false, ninByNin->movesExist());
}

