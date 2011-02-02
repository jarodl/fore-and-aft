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
#include <queue>

class Solver : public Graph<Board>
{
  public:
    Solver(Board b)
    {
      initialBoard = b;
      solutionFound = false;
      Board *goal = new Board(b.getWidth(), b.getHeight());
      goal->clearValues('B', 'R');
      goalKey = hashBoard(goal->getValues());
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
          int hash = hashBoard(b.getValues());
          if (!nodeExists(hash))
            addNeighborToNode(hash, b, n->key, n->data);

          std::vector<Node *>::iterator i;
          for (i = n->neighbors.begin(); i != n->neighbors.end(); i++)
          {
            if ((*i)->key == goalKey)
            {
              std::cout << "Found Solution!" << std::endl;
              return;
            }

            current.push(*i);
          }
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

      //std::vector<Node *>::iterator itr;
      //for (itr = allNodes.begin(); itr != allNodes.end(); itr++)
        //if ((*itr)->visited)
          //std::cout << (*itr)->data << std::endl;
    }

    void dfs()
    {
      Node *currentNode = searchStack.top();
      searchStack.pop();
      currentNode->visited = true;
      
      if (currentNode->key == goalKey)
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
      std::queue<Node *> current;
      Node *start = getNode(hashBoard(initialBoard.getValues()), initialBoard);
      current.push(start);
      start->visited = true;

      while (!current.empty())
      {
        Node *n = current.front();
        current.pop();

        if (n->key == goalKey)
        {
          std::cout << "Found solution!" << std::endl;
          return;
        }

        while (n->data.movesExist())
        {
          Board b = n->data.getCopyAndMakeNextMove();
          int hash = hashBoard(b.getValues());
          if (!nodeExists(hash))
            addNeighborToNode(hash, b, n->key, n->data);
        }

        std::vector<Node *>::iterator itr;
        for (itr = n->neighbors.begin(); itr != n->neighbors.end(); itr++)
        {
          if (!(*itr)->visited)
          {
            current.push(*itr);
            (*itr)->visited = true;
          }
        }
      }
    }

    int hashBoard(const std::string &values)
    {
      int hash = 5381;
      for (unsigned int i = 0; i < values.length(); i++)
        hash = ((hash << 5) + hash) + values[i];

      return hash;
    }

    ~Solver()
    {
    }

  public:
    Board initialBoard;
    int goalKey;
    std::stack<Node *> searchStack;
    bool solutionFound;
};

#endif
