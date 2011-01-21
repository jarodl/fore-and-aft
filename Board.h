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

#include <vector>
#include <iomanip>
#include "Token.h"

#include <iostream>

#define UPPER_LEFT 'R'
#define LOWER_RIGHT 'B'
#define INVALID 'X'
#define OPEN '_'

class Board
{
  public:
    Board(int w, int h) : squares(w, std::vector<Token>(h))
    {
      width = w;
      height = h;

      resetBoard();
    }

    void resetBoard()
    {
      int xOffset = width/2;
      int yOffset = height/2;

      for (int x = 0; x < squares.size(); x++)
      {
        for (int y = 0; y < squares[x].size(); y++)
        {
          if ((x < squares.size() - xOffset ) &&
              (y < squares[x].size() - yOffset))
          {
            squares[x][y] = Token(x, y, UPPER_LEFT);
          }
          else if ((x >= xOffset) && (y >= yOffset))
          {
            squares[x][y] = Token(x, y, LOWER_RIGHT);
          }
          // Invalid move
          else
          {
            squares[x][y] = Token(x, y, INVALID);
          }
        }
      }

      // Set center to open
      squares[xOffset][yOffset] = Token(xOffset, yOffset, OPEN);
    }

    void move(Token one, Token two)
    {
      Token copy = one;
      squares[one.getX()][one.getY()] = two;
      squares[two.getX()][two.getY()] = copy;
    }

    // TODO: Refactor this shiz.
    bool canMove(const Token token, int x, int y)
    {
      bool canMove = false;

      // check if (x, y) is out of reach or out of the bounds of the board.
      int xDist = abs(x - token.getX());
      int yDist = abs(y - token.getY());
      if (((xDist == 1) != (yDist == 1) ||
          (xDist == 2) != (yDist == 2)) &&
          (x > 0 && y > 0 && x < width - 1 && y < height - 1))
      {
        // moving the token one away so the spot has to be open
        if ((xDist == 1 || yDist == 1) && (squares[x][y] == OPEN))
          canMove = true;
        else
        {
          switch(token.getType())
          {
            case UPPER_LEFT:
              // the token is jumping over another token so the token underneath
              // the jump has to be the opposite type
              if (((xDist == 2) && (squares[x-1][y] == LOWER_RIGHT)) ||
                  ((yDist == 2) && (squares[x][y-1] == LOWER_RIGHT)))
                canMove = true;
              break;
            case LOWER_RIGHT:
              if (((xDist == 2) && (squares[x+1][y] == UPPER_LEFT)) ||
                  ((yDist == 2) && (squares[x][y+1] == UPPER_LEFT)))
                canMove = true;
              break;
            default:
              std::cerr << "Warning: attempting to move an invalid game token." << std::endl;
              canMove = false;
              break;
          }
        }
      }
      else
        std::cerr << "Warning: attempting to move outside of the game board or diagonally." << std::endl;

      return canMove;
    }

    void testCanMove()
    {
      std::cout << "Should be false: " << std::endl;
      Token t = squares[0][0];
      std::cout << "Can move (0, 0) to (-1, -1): " << canMove(t, 0, 0) << std::endl;
      std::cout << "Can move (0, 0) to (1, 1): " << canMove(t, 1, 1) << std::endl;
      t = squares[2][0];
      std::cout << "Can move (2, 0) to (3, 0): " << canMove(t, 3, 0) << std::endl;
      t = squares[2][2];
      std::cout << "Can move (2, 2) to (3, 3): " << canMove(t, 3, 3) << std::endl;
      t = squares[4][4];
      std::cout << "Can move (4, 4) to (3, 3): " << canMove(t, 3, 3) << std::endl;
      std::cout << "Can move (4, 4) to (3, 2): " << canMove(t, 3, 2) << std::endl;
      t = squares[2][4];
      std::cout << "Can move (2, 4) to (2, 2): " << canMove(t, 2, 2) << std::endl;
      std::cout << std::endl;

      std::cout << "Should be true: " << std::endl;
      t = squares[1][2];
      std::cout << "Can move (1, 2) to (2, 2): " << canMove(t, 2, 2) << std::endl;
      t = squares[3][2];
      std::cout << "Can move (3, 2) to (2, 2): " << canMove(t, 2, 2) << std::endl;
      std::cout << "Can move (4, 2) to (2, 2): " << canMove(t, 2, 2) << std::endl;
      t = squares[2][3];
      std::cout << "Can move (2, 3) to (2, 2): " << canMove(t, 2, 2) << std::endl;
      std::cout << std::endl;

      std::cout << "Should display a warning: " << std::endl;
      canMove(t, -1, -1);
      t = squares[4][0];
      canMove(t, 4, 1);
      std::cout << std::endl;
    }

    friend std::ostream& operator<< (std::ostream& output,
        const Board& b)
    {
      for (int i = 0; i < b.squares.size(); i++)
      {
        for (int j = 0; j < b.squares[i].size(); j++)
        {
          output << std::setw(2) << b.squares[i][j].getType();
        }
        output << std::endl;
      }
        
      return output;
    }
    
  private:
    int height;
    int width;
  public:
    std::vector< std::vector<Token> > squares;
};

#endif
