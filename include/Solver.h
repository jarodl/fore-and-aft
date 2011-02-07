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
#include <vector>

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
    Solver()
    {
    }

    // Function: Solver
    //
    // Desc: Constructs a new Solver object.
    //
    // Pre: Takes a Board object.
    //
    // Post: A new solver is returned.
    Solver(Board b)
    {
      initialBoard = b;
      solutionFound = false;
      nodesInSolution = 0;
      nodesExpanded = 0;

      Board *goal = new Board(b.getWidth(), b.getHeight());
      goal->clearValues('B', 'R');
      goalKey = hashBoard(goal->getValues());
      delete goal;
      goal = NULL;
    }

    // Function: storeSolution
    //
    // Desc: Pushes the visited nodes into a vector for output and counting.
    //
    // Pre:
    //
    // Post: The number of nodes used are counted and stored in the solution
    // vector.
    void storeSolution()
    {
      solution = std::vector<Node *>();

      std::map<int, Node *>::iterator itr;
      for (itr = nodeMap.begin(); itr != nodeMap.end(); itr++)
      {
        if ((*itr).second->visited)
        {
          nodesInSolution += 1;
          solution.push_back((*itr).second);
        }
      }
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
    }

    // Function: depthFirstSearch
    //
    // Desc: Calls the recursive dfs() function which performs a depth first
    // search on the node map.
    //
    // Pre:
    //
    // Post: DFS is ran.
    void depthFirstSearch()
    {
      Node *start = getNode(hashBoard(initialBoard.getValues()), initialBoard);
      dfs(start);
      storeSolution();
    }

    // Function: breadthFirstSearch
    //
    // Desc: Runs a breadthFirstSearch on the nodeMap.
    //
    // Pre:
    //
    // Post: A BFS is ran and nodes are marked as visited.
    void breadthFirstSearch()
    {
      std::queue<Node *> current;
      Node *start = getNode(hashBoard(initialBoard.getValues()), initialBoard);
      nodesExpanded += 1;
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
            {
              addNeighborToNode(hash, b, n->key, n->data);
              nodesExpanded += 1;
            }
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
        else
          return;

        n->visited = false;
      }

      storeSolution();
    }

    // Function: hashBoard
    //
    // Desc: Hashing function. Returns a unique value for a given string.
    //
    // Pre:
    //
    // Post: Integer corresponding to a string is returned.
    int hashBoard(const std::string &values)
    {
      int hash = 5381;
      for (unsigned int i = 0; i < values.length(); i++)
        hash = ((hash << 5) + hash) + values[i];

      return hash;
    }

    // Function: getNodesInSolution
    //
    // Desc: Returns the number of nodes in the solution.
    //
    // Pre:
    //
    // Post: The number of nodes in the solution is returned.
    int getNodesInSolution() const
    {
      return nodesInSolution;
    }

    // Function: getNodesExpanded
    //
    // Desc: Returns the number of nodes expanded by the solver.
    //
    // Pre:
    //
    // Post: Number of nodes expanded is returned.
    int getNodesExpanded() const
    {
      return nodesExpanded;
    }

    // Function: ~Solver
    //
    // Desc: Deconstructs the Solver.
    //
    // Pre:
    //
    // Post: 
    ~Solver()
    {
    }

    // Function: outputSolution
    //
    // Desc: Writes the solution to an output stream.
    //
    // Pre:
    //
    // Post: The solution is written to an output stream.
    void outputSolution(std::ostream &out)
    {
      std::vector<Node *>::iterator itr;
      for (itr = solution.begin(); itr != solution.end(); itr++)
        out << (*itr)->data << std::endl;
    }

    // Function: <<
    //
    // Desc: Outputs stats about the solved board.
    //
    // Pre:
    //
    // Post: 
    friend std::ostream& operator<<(std::ostream &out, const Solver &s)
    {
      out << std::endl
          << "Nodes expanded: " << s.getNodesExpanded() << std::endl
          << "Nodes in solution: " << s.getNodesInSolution() << std::endl;

      return out;
    }

  private:

    // Function: dfs
    //
    // Desc: Recursive DFS function to traverse a graph.
    //
    // Pre: The node to perform DFS on.
    //
    // Post: A node is traversed and dfs is called again if there is another
    // available node.
    void dfs(Node *currentNode)
    {
      nodesExpanded += 1;
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

    std::vector<Node *> solution;
    Board initialBoard;
    int nodesExpanded;
    int nodesInSolution;
    int goalKey;
    bool solutionFound;
};

#endif
