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

#include <iostream>
#include "Board.h"
#include "Graph.h"
#include <stack>

class Solver : public Graph<Board>
{
  public:
    Solver(Board b)
    {
      initialBoard = b;
      solutionFound = false;
      goal = Board(b.getWidth(), b.getHeight());
      goal.clearValues('B', 'R');
    }

    void depthFirstSearch()
    {
      while (!searchStack.empty())
        searchStack.pop();

      Node *start = getNode(initialBoard.getValues(), initialBoard);
      searchStack.push(start);
      dfs();
    }

    void dfs()
    {
      if (solutionFound)
        return;

      Node *currentNode = searchStack.top();
      searchStack.pop();
      currentNode->visited = true;
      
      //std::cout << currentNode->data << std::endl;

      if (currentNode->data == goal)
      {
        std::cout << "SOLUTION FOUND" << std::endl;
        solutionFound = true;
        return;
      }
      else
      {
        while (currentNode->data.movesExist())
        {
          Board b = currentNode->data.getCopyAndMakeNextMove();
          addNeighborToNode(b.getValues(), b, currentNode->data.getValues(), currentNode->data);
        }

        for (unsigned int i = 0; i < currentNode->neighbors.size(); i++)
        {
          searchStack.push(currentNode->neighbors.at(i));
          dfs();
        }
      }

      currentNode->visited = false;
    }

    void breadthFirstSearch()
    {
    }

    ~Solver()
    {
    }

  public:
    Board initialBoard;
    Board goal;
    std::stack<Node *> searchStack;
    bool solutionFound;
};

#endif
