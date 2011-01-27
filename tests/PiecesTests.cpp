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

TEST_GROUP(InitPieces)
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

TEST_GROUP(FirstMovePieces)
{
  Pieces* fiveByFive;
  Pieces* sevBySev;
  Pieces* ninByNin;

  void setup()
  {
    fiveByFive = new Pieces(5, 5);
    sevBySev = new Pieces(7, 7);
    ninByNin = new Pieces(9, 9);

    fiveByFive->makeNextMove();
    sevBySev->makeNextMove();
    ninByNin->makeNextMove();
  }

  void teardown()
  {
    delete fiveByFive;
    delete sevBySev;
    delete ninByNin;
  }
};

TEST(InitPieces, testPiecesStringSize)
{
  CHECK_EQUAL(17, fiveByFive->getSize());
  CHECK_EQUAL(31, sevBySev->getSize());
  CHECK_EQUAL(49, ninByNin->getSize());
}

TEST(InitPieces, testPiecesClearsValues)
{
  char fiveExpected[] = "RRRRRRRR_BBBBBBBB";
  STRCMP_EQUAL(fiveExpected, fiveByFive->getValues().c_str());
  char sevExpected[] = "RRRRRRRRRRRRRRR_BBBBBBBBBBBBBBB";
  STRCMP_EQUAL(sevExpected, sevBySev->getValues().c_str());
  char ninExpected[] = "RRRRRRRRRRRRRRRRRRRRRRRR_BBBBBBBBBBBBBBBBBBBBBBBB";
  STRCMP_EQUAL(ninExpected, ninByNin->getValues().c_str());
}

TEST(InitPieces, testPiecesMovesDoNotExist)
{
  CHECK_EQUAL(true, fiveByFive->movesExist());
  CHECK_EQUAL(true, sevBySev->movesExist());
  CHECK_EQUAL(true, ninByNin->movesExist());
}

TEST(InitPieces, testPiecesFindsFirstLeftMove)
{
  CHECK_EQUAL(7, fiveByFive->peekAtNextMove());
  CHECK_EQUAL(14, sevBySev->peekAtNextMove());
  CHECK_EQUAL(23, ninByNin->peekAtNextMove());
}

TEST(InitPieces, testPiecesParams)
{
  char fiveExpected[] = "8 2 10 14 6";
  STRCMP_EQUAL(fiveExpected, fiveByFive->paramDebugString().c_str());

  char sevExpected[] = "15 3 18 27 12";
  STRCMP_EQUAL(sevExpected, sevBySev->paramDebugString().c_str());

  char ninExpected[] = "24 4 28 44 20";
  STRCMP_EQUAL(ninExpected, ninByNin->paramDebugString().c_str());
}

TEST(FirstMovePieces, testPiecesMakesNextMove)
{
  char fiveExpected[] = "RRRRRRR_RBBBBBBBB";
  STRCMP_EQUAL(fiveExpected, fiveByFive->getValues().c_str());

  char sevExpected[] = "RRRRRRRRRRRRRR_RBBBBBBBBBBBBBBB";
  STRCMP_EQUAL(sevExpected, sevBySev->getValues().c_str());

  char ninExpected[] = "RRRRRRRRRRRRRRRRRRRRRRR_RBBBBBBBBBBBBBBBBBBBBBBBB";
  STRCMP_EQUAL(ninExpected, ninByNin->getValues().c_str());
}

TEST(FirstMovePieces, testPiecesParams)
{
  char fiveExpected[] = "7 1 10 7 6";
  STRCMP_EQUAL(fiveExpected, fiveByFive->paramDebugString().c_str());

  char sevExpected[] = "14 2 18 14 12";
  STRCMP_EQUAL(sevExpected, sevBySev->paramDebugString().c_str());

  char ninExpected[] = "23 3 28 23 20";
  STRCMP_EQUAL(ninExpected, ninByNin->paramDebugString().c_str());
}

TEST(FirstMovePieces, testPiecesFindsFirstUpMove)
{
  CHECK_EQUAL(6, fiveByFive->peekAtNextMove());
}
