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
#include <stack>
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
    Board(int w, int h) : squares(h, std::vector<Token>(w))
    {
      width = w;
      height = h;

      resetBoard();
      determinePossibleMoves();
    }

    void resetBoard()
    {
      int xOffset = width/2;
      int yOffset = height/2;

      for (unsigned int x = 0; x < squares.size(); x++)
      {
        for (unsigned int y = 0; y < squares[x].size(); y++)
        {
          if ((x < squares.size() - xOffset ) &&
              (y < squares[x].size() - yOffset))
          {
            squares[x][y] = Token(UPPER_LEFT);
          }
          else if (((int)x >= xOffset) && ((int)y >= yOffset))
          {
            squares[x][y] = Token(LOWER_RIGHT);
          }
          // Invalid move
          else
          {
            squares[x][y] = Token(INVALID);
          }
        }
      }

      // Set center to open
      squares[xOffset][yOffset] = Token(OPEN);
    }

    std::vector<Board> getAllPossibleStates()
    {
      std::vector<Board> generatedBoards;
      // Visits each Token in the movableTokens vector, moves the token and
      // copies that state.
      //
      // For each token visited the board generated from moving it will be added
      // to the returned vector in this function.
      //
      // If the graph keeps calling this on every generated board then all
      // possible moves will be added to the graph.
      //
      // The boards generated from this function will be added to the adjency
      // list for *this* board.

      return generatedBoards;
    }

    void determinePossibleMoves()
    {
      // Clear the stack of tokens since the possible moves have changed.
      while (!movableTokens.empty())
        movableTokens.pop();

      for (unsigned int x = 0; x < squares.size(); x++)
      {
        for (unsigned int y = 0; y < squares[x].size(); y++)
        {
          updateMovesForToken(x, y);

          Token *t = &squares[x][y];
          // Keep track of tokens that can be moved to another state
          if (t->getNeighbors().size() > 0)
            movableTokens.push(t);
        }
      }
    }

    void updateMovesForToken(int x, int y)
    {
      Token *t = &squares[x][y];

      if (t->getType() == UPPER_LEFT)
      {
        for (int i = 1; i <= 2; i++)
        {
          if (canMove(t, x, y, x + i, y))
            t->addNeighbor(squares[x + i][y]);
          if (canMove(t, x, y, x, y + i))
            t->addNeighbor(squares[x][y + i]);
        }
      }
      else if (t->getType() == LOWER_RIGHT)
      {
        for (int i = 1; i <= 2; i++)
        {
          if (canMove(t, x, y, x - i, y))
            t->addNeighbor(squares[x - i][y]);
          if (canMove(t, x, y, x, y - i))
            t->addNeighbor(squares[x][y - i]);
        }
      }
    }

    void move(Token &one, Token &two)
    {
      Token copy = one;
      one = two;
      two = copy;
    }

    void testMove()
    {
      move(squares[2][1], squares[2][2]);
      move(squares[2][0], squares[2][1]);
    }

    bool canMove(const Token *token, int fromX, int fromY, int toX, int toY)
    {
      bool canMove = false;
      // check if (x, y) is out of reach or out of the bounds of the board.
      int xDist = abs(fromX - toX);
      int yDist = abs(fromY - toY);

      if (((xDist == 1) != (yDist == 1) ||
          (xDist == 2) != (yDist == 2)) &&
          (toX > 0 && toY > 0 && toX < width - 1 && toY < height - 1))
      {
        // moving the token one away so the spot has to be open
        if ((xDist == 1 || yDist == 1) && (squares[toX][toY] == OPEN))
          canMove = true;
        else
        {
          switch(token->getType())
          {
            case UPPER_LEFT:
              // the token is jumping over another token so the token underneath
              // the jump has to be the opposite type
              if (((xDist == 2) && (squares[toX-1][toY] == LOWER_RIGHT)) ||
                  ((yDist == 2) && (squares[toX][toY-1] == LOWER_RIGHT)))
                canMove = true;
              break;
            case LOWER_RIGHT:
              if (((xDist == 2) && (squares[toX+1][toY] == UPPER_LEFT)) ||
                  ((yDist == 2) && (squares[toX][toY+1] == UPPER_LEFT)))
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
      //std::cout << "Should be false: " << std::endl;
      //Token *t = &squares[0][0];
      //std::cout << "Can move (0, 0) to (-1, -1): " << canMove(t, 0, 0) << std::endl;
      //std::cout << "Can move (0, 0) to (1, 1): " << canMove(t, 1, 1) << std::endl;
      //t = &squares[2][0];
      //std::cout << "Can move (2, 0) to (3, 0): " << canMove(t, 3, 0) << std::endl;
      //t = &squares[2][2];
      //std::cout << "Can move (2, 2) to (3, 3): " << canMove(t, 3, 3) << std::endl;
      //t = &squares[4][4];
      //std::cout << "Can move (4, 4) to (3, 3): " << canMove(t, 3, 3) << std::endl;
      //std::cout << "Can move (4, 4) to (3, 2): " << canMove(t, 3, 2) << std::endl;
      //t = &squares[2][4];
      //std::cout << "Can move (2, 4) to (2, 2): " << canMove(t, 2, 2) << std::endl;
      //std::cout << std::endl;

      //std::cout << "Should be true: " << std::endl;
      //t = &squares[1][2];
      //std::cout << "Can move (1, 2) to (2, 2): " << canMove(t, 2, 2) << std::endl;
      //t = &squares[3][2];
      //std::cout << "Can move (3, 2) to (2, 2): " << canMove(t, 2, 2) << std::endl;
      //std::cout << "Can move (4, 2) to (2, 2): " << canMove(t, 2, 2) << std::endl;
      //t = &squares[2][3];
      //std::cout << "Can move (2, 3) to (2, 2): " << canMove(t, 2, 2) << std::endl;
      //std::cout << std::endl;

      //std::cout << "Should display a warning: " << std::endl;
      //canMove(t, -1, -1);
      //t = &squares[4][0];
      //canMove(t, 4, 1);
      //std::cout << std::endl;
    }

    friend std::ostream& operator<< (std::ostream& output,
        const Board& b)
    {
      // DEBUGGING
      output << "    ";
      for (int i = 0; i < b.width; i++)
        output << std::setw(7) << i;
      output << std::endl;

      for (unsigned int i = 0; i < b.squares.size(); i++)
      {
        // DEBUGGING
        output << std::setw(4) << i;
        for (unsigned int j = 0; j < b.squares[i].size(); j++)
          output << std::setw(4) << b.squares[j][i].getType() << "(" << b.squares[j][i].getNeighbors().size() << ")";
        output << std::endl;
      }
        
      return output;
    }
    
  private:
    int height;
    int width;
  public:
    std::stack< Token* > movableTokens;
    std::vector< std::vector<Token> > squares;
};

#endif
