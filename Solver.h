/*
 * =====================================================================================
 *
 *       Filename:  Solver.h
 *
 *    Description:  Manages the boards in an attempt to find a solution.
 *
 *        Version:  1.0
 *        Created:  01/21/2011 01:52:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jarod Luebbert (), jarodluebbert@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SOLVER_H
#define SOLVER_H

#include "Board.h"

class Solver
{
  private:
    struct Node
    {
      Node(Board b) : data(b)
      {
        // TODO:
        // this could be very bad
        std::vector<Board> boardStates = data.getNextBoards();
        for (unsigned int i = 0; i < boardStates.size(); i++)
        {
          std::cout << boardStates.at(i) << std::endl;
          //if (boardStates.at(i).movableTokens.size() > 0)
            //states.push_back(Node(boardStates.at(i)));
        }
      }

      bool visited;
      Board data;
      std::vector<Node> states;
    };

  public:
    Solver()
    {
    }

    Solver(int boardWidth, int boardHeight)
    {
      startingBoard = new Board(boardWidth, boardHeight);
      // All possible states from an initial board
      std::vector<Board> initialStates = startingBoard->getNextBoards();
      for (unsigned int i = 0; i < initialStates.size(); i++)
      {
        //std::cout << initialStates.at(i);
        nodes.push_back(Node(initialStates.at(i)));
      }

      std::cout << *startingBoard << std::endl;
    }

    ~Solver()
    {
      delete startingBoard;
      startingBoard = NULL;
    }

    void fillNode(Node &n)
    {
      // TODO:
      // Put this in the node constructor?
      //n.states = n.data.getNextBoards();
      //for (unsigned int i = 0; i < n.states.size(); i++)
        //fillNode(n.states.at(i));
    }

    friend std::ostream& operator<< (std::ostream& output,
        const Solver& s)
    {
      // output all boards
      for (unsigned int i = 0; i < s.nodes.size(); i++)
      {
        output << s.nodes.at(i).data << std::endl;
      }

      return output;
    }

  public:
    Board *startingBoard;
    std::vector<Node> nodes;
    //Graph<Board> graph;
};

#endif
