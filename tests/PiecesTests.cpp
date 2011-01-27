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

TEST(InitPieces, testPiecesMovesExist)
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

TEST(InitPieces, testGetCopyAndMakeMove)
{
  Pieces cpy = fiveByFive->getCopyAndMakeNextMove();
  char cpyExpected[] = "RRRRRRR_RBBBBBBBB";
  STRCMP_EQUAL(cpyExpected, cpy.getValues().c_str());
}

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

TEST(FirstMovePieces, testPiecesFindsSecondMove)
{
  CHECK_EQUAL(6, fiveByFive->peekAtNextMove());
  CHECK_EQUAL(13, sevBySev->peekAtNextMove());
  CHECK_EQUAL(22, ninByNin->peekAtNextMove());
}

TEST_GROUP(SecondMovePieces)
{
  Pieces* fiveByFive;
  Pieces* sevBySev;
  Pieces* ninByNin;

  void setup()
  {
    fiveByFive = new Pieces(5, 5);
    sevBySev = new Pieces(7, 7);
    ninByNin = new Pieces(9, 9);

    for (int i = 0; i < 2; i++)
    {
      fiveByFive->makeNextMove();
      sevBySev->makeNextMove();
      ninByNin->makeNextMove();
    }
  }

  void teardown()
  {
    delete fiveByFive;
    delete sevBySev;
    delete ninByNin;
  }
};

TEST(SecondMovePieces, testSecondPiecesParams)
{
  char fiveExpected[] = "6 0 10 6 6";
  STRCMP_EQUAL(fiveExpected, fiveByFive->paramDebugString().c_str());

  char sevExpected[] = "13 1 18 13 12";
  STRCMP_EQUAL(sevExpected, sevBySev->paramDebugString().c_str());

  char ninExpected[] = "22 2 28 22 20";
  STRCMP_EQUAL(ninExpected, ninByNin->paramDebugString().c_str());
}

TEST(SecondMovePieces, testPiecesFindThirdMove)
{
  CHECK_EQUAL(3, fiveByFive->peekAtNextMove());
  CHECK_EQUAL(12, sevBySev->peekAtNextMove());
  CHECK_EQUAL(21, ninByNin->peekAtNextMove());
}

TEST_GROUP(ThirdMovePieces)
{
  Pieces* fiveByFive;
  Pieces* sevBySev;
  Pieces* ninByNin;

  void setup()
  {
    fiveByFive = new Pieces(5, 5);
    sevBySev = new Pieces(7, 7);
    ninByNin = new Pieces(9, 9);

    for (int i = 0; i < 3; i++)
    {
      fiveByFive->makeNextMove();
      sevBySev->makeNextMove();
      ninByNin->makeNextMove();
    }
  }

  void teardown()
  {
    delete fiveByFive;
    delete sevBySev;
    delete ninByNin;
  }
};

TEST(ThirdMovePieces, testThirdPiecesParams)
{
  char fiveExpected[] = "3 0 5 6 3";
  STRCMP_EQUAL(fiveExpected, fiveByFive->paramDebugString().c_str());

  char sevExpected[] = "12 0 18 12 12";
  STRCMP_EQUAL(sevExpected, sevBySev->paramDebugString().c_str());

  char ninExpected[] = "21 1 28 21 20";
  STRCMP_EQUAL(ninExpected, ninByNin->paramDebugString().c_str());
}

TEST(ThirdMovePieces, testPiecesFindFourthMove)
{
  CHECK_EQUAL(0, fiveByFive->peekAtNextMove());
  CHECK_EQUAL(8, sevBySev->peekAtNextMove());
  CHECK_EQUAL(20, ninByNin->peekAtNextMove());
}

TEST_GROUP(FourthMovePieces)
{
  Pieces* fiveByFive;

  void setup()
  {
    fiveByFive = new Pieces(5, 5);

    for (int i = 0; i < 4; i++)
      fiveByFive->makeNextMove();
  }

  void teardown()
  {
    delete fiveByFive;
  }
};

TEST(FourthMovePieces, testPiecesFindFifthMove)
{
  CHECK_EQUAL(false, fiveByFive->movesExist());
}
