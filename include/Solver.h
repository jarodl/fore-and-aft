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

#define InitialFNV 2166136261U
#define FNVMultiple 16777619

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

    void nonRecursiveDFS()
    {
      std::stack<Node *> seen;
      std::stack<Node *> current;
      Node *start = getNode(hashBoard(initialBoard.getValues()), initialBoard);
      current.push(start);

      while (!current.empty())
      {
        Node *n = current.top();
        current.pop();
        seen.push(n);

        // get the neighbors
        while (n->data.movesExist())
        {
          Board b = n->data.getCopyAndMakeNextMove();
          addNeighborToNode(hashBoard(b.getValues()), b, n->key, n->data);
        }

        for (unsigned int i = 0; i < n->neighbors.size(); i++)
        {
          if (n->neighbors.at(i)->data == goal)
          {
            std::cout << "Found Solution!" << std::endl;
            return;
          }

          current.push(n->neighbors.at(i));
        }
      }
    }

    void depthFirstSearch()
    {
      while (!searchStack.empty())
        searchStack.pop();

      Node *start = getNode(hashBoard(initialBoard.getValues()), initialBoard);
      searchStack.push(start);
      dfs();
    }

    void dfs()
    {
      Node *currentNode = searchStack.top();
      searchStack.pop();
      currentNode->visited = true;
      
      if (currentNode->data == goal)
      {
        std::cout << "Solution Found" << std::endl;
        solutionFound = true;
        return;
      }
      else
      {
        while (currentNode->data.movesExist())
        {
          Board b = currentNode->data.getCopyAndMakeNextMove();
          int hash = hashBoard(b.getValues());
          if (!nodeExists(hash))
            addNeighborToNode(hash, b, currentNode->key, currentNode->data);

          std::vector<Node *>::iterator itr;
          for (itr = currentNode->neighbors.begin();
              itr != currentNode->neighbors.end(); itr++)
          {
            searchStack.push(*itr);
            dfs();

            if (solutionFound)
              return;
          }
        }
      }

      currentNode->visited = false;
    }

    void breadthFirstSearch()
    {
    }

    int hashBoard(const std::string &values)
    {
      int hash = InitialFNV;

      for (int i = 0; i < (int)values.length(); i++)
      {
        hash = hash ^ (values[i]);
        hash = hash * FNVMultiple;
      }

      return hash;
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
