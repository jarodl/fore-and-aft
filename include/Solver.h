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
#include <stack>
#include <queue>

#include "Board.h"
#include "Graph.h"

class Solver : public Graph<Board>
{
  public:

    // Function: Solver
    //
    // Desc:
    //
    // Pre:
    //
    // Post: 
    Solver(Board b)
    {
      initialBoard = b;
      solutionFound = false;
      Board *goal = new Board(b.getWidth(), b.getHeight());
      goal->clearValues('B', 'R');
      goalKey = hashBoard(goal->getValues());
    }

    // Function: heuristicSearch
    //
    // Desc:
    //
    // Pre:
    //
    // Post: 
    void heuristicSearch()
    {
      std::stack<Node *> closed;
      std::stack<Node *> open;
    }

    // Function: depthFirstSearch
    //
    // Desc:
    //
    // Pre:
    //
    // Post: 
    void depthFirstSearch()
    {
      Node *start = getNode(hashBoard(initialBoard.getValues()), initialBoard);
      dfs(start);

      std::map<int, Node *>::iterator itr;
      for (itr = nodeMap.begin(); itr != nodeMap.end(); itr++)
        if ((*itr).second->visited)
          std::cout << (*itr).second->data << std::endl;
    }


    // Function: breadthFirstSearch
    //
    // Desc:
    //
    // Pre:
    //
    // Post: 
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

        if (n->key != goalKey)
        {
          n->visited = false;

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
    }

    // Function: hashBoard
    //
    // Desc:
    //
    // Pre:
    //
    // Post: 
    int hashBoard(const std::string &values)
    {
      int hash = 5381;
      for (unsigned int i = 0; i < values.length(); i++)
        hash = ((hash << 5) + hash) + values[i];

      return hash;
    }

    // Function: ~Solver
    //
    // Desc:
    //
    // Pre:
    //
    // Post: 
    ~Solver()
    {
    }

  private:

    // Function: dfs
    //
    // Desc:
    //
    // Pre:
    //
    // Post: 
    void dfs(Node *currentNode)
    {
      currentNode->visited = true;
      
      if (currentNode->key == goalKey)
      {
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
            dfs(*itr);

            if (solutionFound)
              return;
          }
        }
      }

      currentNode->visited = false;
    }

    Board initialBoard;
    int goalKey;
    bool solutionFound;
};

#endif
