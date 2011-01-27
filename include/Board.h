/*
 * =====================================================================================
 *
 *       Filename:  Board.h
 *
 *    Description:  A game board for moving tokens around.
 *
 *        Version:  1.0
 *        Created:  01/20/2011 13:56:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jarod Luebbert (), jarodluebbert@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef BOARD_H
#define BOARD_H

#include <iomanip>
#include <iostream>
#include <vector>

#define UPPER_LEFT 'R'
#define LOWER_RIGHT 'B'
#define INVALID 'X'
#define OPEN '_'

class Board
{
  public:
    Board()
    {
    }

    Board(int w, int h)
    {
      width = w;
      height = h;
    }

    Board(const Board &cpy)
    {
      width = cpy.getWidth();
      height = cpy.getHeight();
    }

    ~Board()
    {
    }

    Board getNextBoard()
    {
      Board newBoard = Board(*this);

      return newBoard;
    }

    std::vector<Board> getEveryNextBoard()
    {
      std::vector<Board> everyBoard;

      return everyBoard;
    }

    friend std::ostream& operator<< (std::ostream& output, const Board& b)
    {
      return output;
    }

    int getWidth() const
    {
      return width;
    }

    int getHeight() const
    {
      return height;
    }

  private:
    int width, height;
};

#endif
