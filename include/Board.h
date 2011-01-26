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
      pieces.resize((w * h) - ((h - 1) * (w / 2)));

      clearBoard(UPPER_LEFT, LOWER_RIGHT);
      updatePossibleMovesAroundOpen(openLocation);
    }

    Board(const Board &cpy)
    {
      width = cpy.getWidth();
      height = cpy.getHeight();
      pieces = cpy.getPieces();
      openLocation = cpy.getOpenLocation();
      updatePossibleMovesAroundOpen(openLocation);
    }

    ~Board()
    {
    }

    void clearBoard(char upperLeft, char lowerRight)
    {
      int boardSize = pieces.size();

      for (int i = 0; i < boardSize; i++)
      {
        if (i < boardSize/2)
          pieces[i] = upperLeft;
        else if (i > boardSize/2)
          pieces[i] = lowerRight;
        else
        {
          pieces[i] = OPEN;
          openLocation = i;
        }
      }
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
      updatePossibleMovesAroundOpen(openLocation);
    }

    void updateHelper(int i, int left, int right, int start, int end)
    {
      int offset = (width / 2) + 1;
      //std::cout << "Offset: " << offset << std::endl;

      //std::cout << "at: " << i << " left = " << left << ", right = " << right << std::endl;
      //std::cout << "top: " << start << " bottom: " << end << std::endl;

      int pos = i - 1;
      if (pos >= left && pieces[pos] == UPPER_LEFT)
        pieceMoves.push(pos);

      pos = i + 1;
      if (pos <= right && pieces[pos] == LOWER_RIGHT)
        pieceMoves.push(pos);

      pos = i + 2;
      if (pos <= right && pieces[pos] == LOWER_RIGHT &&
          pieces[i + 1] == UPPER_LEFT)
        pieceMoves.push(pos);

      pos = i - 2;
      if (pos >= left && pieces[pos] == UPPER_LEFT &&
          pieces[i - 1] == LOWER_RIGHT)
        pieceMoves.push(pos);

      pos = i - offset;
      if (pos >= start && pieces[pos] == UPPER_LEFT)
        pieceMoves.push(pos);

      pos = i + offset;
      if (pos <= end && pieces[pos] == LOWER_RIGHT)
        pieceMoves.push(pos);

      pos = i - (offset * 2);
      if (pos >= start && pieces[pos] == UPPER_LEFT &&
          pieces[i - offset] == LOWER_RIGHT)
        pieceMoves.push(pos);

      pos = i + (offset * 2);
      if (pos <= end && pieces[pos] == LOWER_RIGHT &&
          pieces[i - offset] == LOWER_RIGHT)
        pieceMoves.push(pos);
    }

    void updatePossibleMovesAroundOpen(int index)
    {
      clearMoves();
      int x, y, left, right;
      int middle = pieces.size() / 2;
      int offset = (width / 2);
      int halfWidth = (width / 2) + 1;
      bool middleRow = (index > middle - halfWidth && index < middle + halfWidth);

      // Lower right
      if (index > middle)
      {
        y = ((index - ((halfWidth * halfWidth) - 1)) / halfWidth);
        x = ((index - ((halfWidth * halfWidth) - 1)) - (y * halfWidth));
        left = middleRow ? index - (offset - x) - offset : index - x;
        right = index + (offset - x);
      }
      // Upper left
      else
      {
          y = (index / halfWidth);
          x = (index - (y * halfWidth));
          left = index - x;
          right = middleRow ? index + (offset - x) + offset : index + (offset - x);
      }

      int top = index - (halfWidth * y);
      int bottom = (index == middle) ? index + (halfWidth * y) : index + (halfWidth * (offset - y));

      //std::cout << "offset: " << offset << " halfWidth: " << halfWidth << std::endl;
      //std::cout << "x: " << x << " y: " << y << std::endl;

      updateHelper(index, left, right, top, bottom);
    }

    friend std::ostream& operator<< (std::ostream& output, const Board& b)
    {
      //for (int i = 0; i < b.getWidth(); i++)
      //{
        //for (int i = 0; i < b.getHeight(); i++)
        //{

        //}
        //output << std::endl;
      //}
      output << b.getPieces() << std::endl;
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

    int getOpenLocation() const
    {
      return openLocation;
    }

    std::string getPieces() const
    {
      return pieces;
    }

    int width, height;
    std::string pieces;
    std::stack<int> pieceMoves;
    int openLocation;
};

#endif
