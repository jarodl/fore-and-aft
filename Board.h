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
      resetBoard(UPPER_LEFT, LOWER_RIGHT);
      determinePossibleMoves();
    }

    Board(const Board &cpy) : squares(cpy.squares)
    {
      determinePossibleMoves();
    }

    void resetBoard(char upperLeft, char lowerRight)
    {
      int xOffset = squares.size()/2;
      int yOffset = squares[0].size()/2;

      for (unsigned int x = 0; x < squares.size(); x++)
      {
        for (unsigned int y = 0; y < squares[x].size(); y++)
        {
          if ((x < squares.size() - xOffset ) &&
              (y < squares[x].size() - yOffset))
          {
            squares[x][y] = Token(upperLeft);
          }
          else if (((int)x >= xOffset) && ((int)y >= yOffset))
          {
            squares[x][y] = Token(lowerRight);
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

    std::vector<Board> getNextBoards()
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
      //unsigned int numOfMovableTokens = movableTokens.size();
      //for (unsigned int i = 0; i < numOfMovableTokens; i++)
      while (!movableTokens.empty())
      {
        Token *movableToken = movableTokens.top();
        // The token we are going to move could have more than one possible
        // location to move to.
        std::vector<Token*> placesToMove = movableToken->getNeighbors();

        // So generate a board for each possible location to move
        for (unsigned int j = 0; j < placesToMove.size(); j++)
        {
          // TODO:
          // FUUUU. Since we don't have the location of the two tokens we want
          // to move it looks like the best option is to move the token, copy
          // the board and then move it back on the original board
          //newState.moveToken(*movableToken, placesToMove.at(j));
          move(*movableToken, *placesToMove.at(j));
          // Copy the current board
          Board newState = Board(*this);
          //TODO:
          //DEBUG
          //std::cout << newState << std::endl;
          generatedBoards.push_back(newState);
          // move the token back where it was
          move(*movableToken, *placesToMove.at(j));
        }

        // Remove the move we are making from the movableTokens stack so we
        // don't assume we can make that move in the next state.
        movableTokens.pop();
      }

      return generatedBoards;
    }

    void determinePossibleMoves()
    {

      // TODO:
      // This function can run significantly faster by only checking the
      // locations of the two tokens that were swapped.
      // DO IT!

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
      t->removeAllNeighbors();

      if (t->getType() == UPPER_LEFT)
      {
        for (int i = 1; i <= 2; i++)
        {
          if (canMove(t, x, y, x + i, y))
            t->addNeighbor(&squares[x + i][y]);
          else if (canMove(t, x, y, x, y + i))
            t->addNeighbor(&squares[x][y + i]);
        }
      }
      else if (t->getType() == LOWER_RIGHT)
      {
        for (int i = 1; i <= 2; i++)
        {
          if (canMove(t, x, y, x - i, y))
            t->addNeighbor(&squares[x - i][y]);
          else if (canMove(t, x, y, x, y - i))
            t->addNeighbor(&squares[x][y - i]);
        }
      }
    }

    void move(Token &one, Token &two)
    {
      Token copy = one;
      one = two;
      two = copy;
    }

    bool canMove(const Token *token, int fromX, int fromY, int toX, int toY)
    {
      bool canMove = false;
      // check if (x, y) is out of reach or out of the bounds of the board.

      // check if the token is moving the wrong direction
      switch(token->getType())
      {
        case UPPER_LEFT:
          if (fromX - toX > 0 || fromY - toY > 0)
            return false;
          break;
        case LOWER_RIGHT:
          if (fromX - toX < 0 || fromY - toY < 0)
            return false;
          break;
      }

      int xDist = abs(fromX - toX);
      int yDist = abs(fromY - toY);

      if (((xDist == 1) != (yDist == 1) ||
          (xDist == 2) != (yDist == 2)) &&
          (toX >= 0 && toY >= 0 && toX < squares.size() && toY < squares[toX].size()) &&
          (squares[toX][toY] == OPEN))
      {
        // moving the token one away so the spot has to be open
        if (xDist == 1 || yDist == 1)
        {
          canMove = true;
        }
        else
        {
          switch(token->getType())
          {
            case UPPER_LEFT:
              // the token is jumping over another token so the token underneath
              // the jump has to be the opposite type
              if (((xDist == 2) && (squares[fromX+1][fromY] == LOWER_RIGHT)) ||
                  ((yDist == 2) && (squares[fromX][fromY+1] == LOWER_RIGHT)))
                canMove = true;
              break;
            case LOWER_RIGHT:
              if (((xDist == 2) && (squares[fromX-1][fromY] == UPPER_LEFT)) ||
                  ((yDist == 2) && (squares[fromX][fromY-1] == UPPER_LEFT)))
                canMove = true;
              break;
            default:
              std::cerr << "Warning: attempting to move an invalid game token." << std::endl;
              canMove = false;
              break;
          }
        }
      }
      //else
        //std::cerr << "Warning: attempting to move outside of the game board or diagonally." << std::endl;

      return canMove;
    }

    friend std::ostream& operator<< (std::ostream& output,
        const Board& b)
    {
      // DEBUGGING
      output << "    ";
      for (int i = 0; i < b.squares.size(); i++)
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

    bool isGoal()
    {
      Board *goalKey = new Board(squares.size(), squares.size());
      goalKey->resetBoard(LOWER_RIGHT, UPPER_LEFT);

      return (*goalKey == *this);
    }

    bool operator==(const Board b)
    {
      for (unsigned int x = 0; x < squares.size(); x++)
        for (unsigned int y = 0; y < squares[x].size(); y++)
          if (b.squares[x][y] != squares[x][y])
            return false;

      return true;
    }

    bool operator!=(const Board b)
    {
      return !(*this == b);
    }
    
  public:
    std::stack<Token*> movableTokens;
    std::vector< std::vector<Token> > squares;
};

#endif
