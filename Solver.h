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
#include <queue>

class Solver
{
  private:
    struct Node
    {
      Node(Board b) : data(b)
      {
        visited = false;
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
      solutionFound = false;
      addNode(Board(boardWidth, boardHeight));
    }

    void searchGoalDF()
    {
      // empty the stack
      while (!searchStack.empty())
        searchStack.pop();

      for (unsigned int i = 0; i < nodes.size(); i++)
      {
        if (!solutionFound)
        {
          searchStack.push(&nodes.at(i));
          depthFirstSearch();
        }
      }
    }

    void searchGoalBF()
    {
      std::queue<Node*> q = std::queue<Node*>();

      Node *currentNode;
      for (unsigned int i = 0; i < nodes.size(); i++)
      {
        currentNode = &nodes.at(i);
        q.push(currentNode);

        while (!q.empty())
        {
          Node *temp = q.front();
          q.pop();

          if (temp->data.isGoal())
          {
          }
        }
      }
    }

    void depthFirstSearch()
    {
      if (solutionFound)
        return;

      Node *currentNode = searchStack.top();
      searchStack.pop();
      currentNode->visited = true;


      if (currentNode->data.isGoal())
      {
        solutionFound = true;
        return;
      }
      else
      {
        // generate new states
        // TODO:
        // Only generate one state here so we don't generate states we end up
        // not using
        std::vector<Board> boards = currentNode->data.getNextBoards();
        for (unsigned int i = 0; i < boards.size(); i++)
          addNeighborToNode(currentNode, boards.at(i));

        for (unsigned int i = 0; i < currentNode->states.size(); i++)
        {
          searchStack.push(currentNode->states.at(i));
          depthFirstSearch();
        }
      }

      while (!searchStack.empty())
      {
        std::cout << searchStack.top()->data << std::endl;
        searchStack.pop();
      }

      currentNode->visited = false;
    }

    ~Solver()
    {
    }

    void addNode(Board b)
    {
      if (!nodeExists(b))
        nodes.push_back(Node(b));
    }

    bool nodeExists(const Board &b)
    {
      for (unsigned int i = 0; i < nodes.size(); i++)
        if (nodes.at(i).data == b)
          return true;

      return false;
    }

    void addNeighborToNode(Node *n, Board &b)
    {
      for (unsigned int i = 0; i < nodes.size(); i++)
      {
        if (nodes.at(i).data == b)
        {
          n->states.push_back(&nodes.at(i));
          return;
        }
      }

      // TODO:
      // This is probably very wrong
      n->states.push_back(new Node(b));
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
    std::vector<Node> nodes;
    std::stack<Node*> searchStack;
    bool solutionFound;
};

#endif
