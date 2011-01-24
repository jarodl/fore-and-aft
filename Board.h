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
#include <string>
#include <vector>
#include <stack>

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
      pieces = "";
      pieces.resize(w * h);

      clearBoard(UPPER_LEFT, LOWER_RIGHT);
      openLocation = pieces.size()/2;
      updatePossibleMovesAroundOpen(openLocation);
    }

    Board(const Board &cpy)
    {
      width = cpy.getWidth();
      height = cpy.getHeight();
      pieces = cpy.getPieces();
      openLocation = cpy.getOpenLocation();
      pieceMoves = cpy.getPieceMoves();
    }

    ~Board()
    {
    }

    void clearBoard(char upperLeft, char lowerRight)
    {
      int boardSize = pieces.size();
      int offset = (boardSize/width) - width/2 - 1;

      for (int i = 0; i < width; i++)
      {
        for (int j = 0; j < height; j++)
        {
          int index = translate(i, j);
          if (i < width - offset && j < height - offset)
            pieces[index] = upperLeft;
          else if (i >= offset && j >= offset)
            pieces[index] = lowerRight;
          else
            pieces[index] = INVALID;
        }
      }

      pieces[boardSize/2] = OPEN;
    }

    Board getNextBoard()
    {
      int from = pieceMoves.top();
      pieceMoves.pop();

      Board newBoard = Board(*this);
      newBoard.move(from, openLocation);

      return newBoard;
    }

    std::vector<Board> getEveryNextBoard()
    {
      std::vector<Board> everyBoard;

      while (!pieceMoves.empty())
        everyBoard.push_back(getNextBoard());

      return everyBoard;
    }

    void move(int from, int to)
    {
      // update the character
      char tmp = pieces[from];
      pieces[from] = pieces[to];
      pieces[to] = tmp;

      openLocation = (pieces[to] == OPEN) ? to : from;
      clearMoves();
      updatePossibleMovesAroundOpen(openLocation);
    }

    void updatePossibleMovesAroundOpen(int index)
    {
      int y = toY(index);
      int x = toX(index, y);

      if (x + 1 < width && pieces[translate(x + 1, y)] == LOWER_RIGHT)
        pieceMoves.push(translate(x + 1, y));

      if (x + 2 < width && pieces[translate(x + 2, y)] == LOWER_RIGHT &&
          pieces[translate(x + 1, y)] == UPPER_LEFT)
        pieceMoves.push(translate(x + 2, y));

      if (x - 1 >= 0 && pieces[translate(x - 1, y)] == UPPER_LEFT)
        pieceMoves.push(translate(x - 1, y));

      if (x - 2 >= 0 && pieces[translate(x - 2, y)] == UPPER_LEFT &&
          pieces[translate(x - 1, y)] == LOWER_RIGHT)
        pieceMoves.push(translate(x - 2, y));

      if (y + 1 < height && pieces[translate(x, y + 1)] == LOWER_RIGHT)
        pieceMoves.push(translate(x, y + 1));

      if (y - 1 >= 0 && pieces[translate(x, y - 1)] == UPPER_LEFT)
        pieceMoves.push(translate(x, y - 1));

      if (y + 2 < height && pieces[translate(x, y + 2)] == LOWER_RIGHT &&
          pieces[translate(x, y + 1)] == UPPER_LEFT)
        pieceMoves.push(translate(x, y + 2));

      if (y - 2 >= 0 && pieces[translate(x, y - 2)] == UPPER_LEFT &&
          pieces[translate(x, y - 1)] == LOWER_RIGHT)
        pieceMoves.push(translate(x, y - 2));
    }

    void updatePossibleMovesFrom(int index)
    {
      int y = toY(index);
      int x = toX(index, y);

      if (pieces[index] == UPPER_LEFT)
      {
        if ((x + 1 < width) && pieces[translate(x + 1, y)] == OPEN)
          pieceMoves.push(translate(x + 1, y));
        else if ((x + 2 < width) && pieces[translate(x + 1, y)] == LOWER_RIGHT
              && pieces[x + 2] == OPEN)
          pieceMoves.push(translate(x + 2, y));
        else if ((y + 1 < height) && pieces[translate(x, y + 1)] == OPEN)
          pieceMoves.push(translate(x, y + 1));
        else if ((y + 2 < height) && pieces[translate(x, y + 1)] == LOWER_RIGHT &&
            pieces[translate(x, y + 2)] == OPEN)
          pieceMoves.push(translate(x, y + 2));
      }
      else if (pieces[index] == LOWER_RIGHT)
      {
        if ((x - 1 >= 0) && pieces[translate(x - 1, y)] == OPEN)
          pieceMoves.push(translate(x - 1, y));
        else if ((x - 2 >= 0) && pieces[translate(x - 1, y) == UPPER_LEFT &&
            pieces[translate(x - 2, y)]] == OPEN)
          pieceMoves.push(translate(x - 2, y));
        else if ((y - 1 >= 0) && pieces[translate(x, y - 1)] == OPEN)
          pieceMoves.push(translate(x, y - 1));
        else if ((y - 2 >= 0) && pieces[translate(x, y - 1)] == UPPER_LEFT &&
            pieces[translate(x, y - 2)] == OPEN)
          pieceMoves.push(translate(x, y - 2));
      }
    }

    friend std::ostream& operator<< (std::ostream& output, const Board& b)
    {
      for (int i = 0; i < b.getWidth(); i++)
      {
        for (int j = 0; j < b.getHeight(); j++)
          output << std::setw(2) << b[b.translate(j, i)];
        output << std::endl;
      }
        
      return output;
    }

    void clearMoves()
    {
      while (!pieceMoves.empty())
        pieceMoves.pop();
    }

    char operator[](const int index) const
    {
      return pieces[index];
    }

    bool operator==(const Board &otherBoard)
    {
      return (pieces == otherBoard.getPieces());
    }

    bool operator!=(const Board &otherBoard)
    {
      return (*this != otherBoard);
    }

    bool operator==(const std::string &otherBoard)
    {
      return (pieces == otherBoard);
    }

    bool operator!=(const std::string &otherBoard)
    {
      return (*this != otherBoard);
    }

    bool movesExist() const
    {
      return (!pieceMoves.empty());
    }

    int getWidth() const
    {
      return width;
    }

    int getHeight() const
    {
      return height;
    }

    int translate(int x, int y) const
    {
      return (x + (y * width));
    }

    int toX(int index, int y) const
    {
      return index - (y * width);
    }

    int toY(int index) const
    {
      return index/width;
    }

    int getOpenLocation() const
    {
      return openLocation;
    }

    std::string getPieces() const
    {
      return pieces;
    }

    std::stack<int> getPieceMoves() const
    {
      return pieceMoves;
    }

  private:
    int width, height;
    std::string pieces;
    std::stack<int> pieceMoves;
    int openLocation;
};

#endif
