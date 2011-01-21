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
#include "Graph.h"

//template <typename T>
class Solver
{
  private:
    //struct Node
    //{
      //bool visited;
      //T data;
    //};

  public:
    Solver()
    {
    }

    Solver(int boardWidth, int boardHeight)
    {
      startingBoard = new Board(boardWidth, boardHeight);
      graph = Graph<Board>();
    }

    ~Solver()
    {
      delete startingBoard;
      startingBoard = NULL;
    }

    void fillGraph()
    {
      graph.add(startingBoard);
    }

  private:
    Board *startingBoard;
    Graph<Board> graph;
};

#endif
