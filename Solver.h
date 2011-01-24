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
      Board initialBoard = Board(boardWidth, boardHeight);
      addNode(initialBoard);

      goal = initialBoard.getPieces();
      std::reverse(goal.begin(), goal.end());
    }

    void searchGoalDF()
    {
      std::stack<Node*> openNodes;
      std::stack<Node*> closedNodes;
      bool solution = false;

      for (unsigned int i = 0; i < nodes.size(); i++)
        openNodes.push(&nodes.at(i));

      while (!openNodes.empty())
      {
        Node *currentNode = openNodes.top();
        openNodes.pop();

        if (goalWasFound(currentNode->data))
        {
          closedNodes.push(currentNode);
          solution = true;
        }
        else if (currentNode->data.movesExist())
        {
          std::vector<Board> boards = currentNode->data.getEveryNextBoard();

          for(unsigned int i = 0; i < boards.size(); i++)
            addNeighborToNode(currentNode, boards.at(i));

          for (unsigned int i = 0; i < currentNode->states.size(); i++)
          {
            openNodes.push(currentNode->states.at(i));
          }

          closedNodes.push(currentNode);
        }

        if (solution)
          break;
      }

      while(!closedNodes.empty())
      {
        std::cout << closedNodes.top()->data << std::endl;
        closedNodes.pop();
      }
    }

    void searchGoalBF()
    {
    }

    void depthFirstSearch()
    {
      if (solutionFound)
        return;

      Node *currentNode = searchStack.top();
      searchStack.pop();
      currentNode->visited = true;

      if (goalWasFound(currentNode->data))
      {
        solutionFound = true;
      }
      else
      {
        // generate new states
        std::vector<Board> boards = currentNode->data.getEveryNextBoard();

        for (unsigned int i = 0; i < boards.size(); i++)
          addNeighborToNode(currentNode, boards.at(i));

        for (unsigned int i = 0; i < currentNode->states.size(); i++)
        {
          searchStack.push(currentNode->states.at(i));
          depthFirstSearch();
        }

        //currentNode->visited = false;
      }
    }

    ~Solver()
    {
    }

    void addNode(Board &b)
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

    bool goalWasFound(const Board &b)
    {
      if (b.getPieces()[b.getOpenLocation()] != goal[goal.size()/2])
        return false;

      return (b.getPieces() == goal);
    }

    friend std::ostream& operator<< (std::ostream& output, const Solver& s)
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
    std::string goal;
    bool solutionFound;
};

#endif
