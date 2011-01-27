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
        visited = false;
      }

      ~Node()
      {
        std::vector<Node*>::iterator it;
        for (it = states.begin(); it < states.end(); it++)
          delete *it;
      }

      bool visited;
      Board data;
      std::vector<Node*> states;
    };

  public:
    Solver()
    {
    }

    Solver(int boardWidth, int boardHeight)
    {
    }

    void searchGoalDF()
    {
    }

    void searchGoalBF()
    {
    }

    ~Solver()
    {
    }
};

#endif
