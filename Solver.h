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
    class Node
    {
      public:
        Node(Board b) : data(b)
        {
          visited = false;
          //if (!data.rejected)
          //{
            //// TODO:
            //// this could be very bad
            //std::vector<Board> boardStates = data.getNextBoards();

            //for (unsigned int i = 0; i < boardStates.size(); i++)
            //{
            //}

            ////bool allStatesAreRejected = true;
            ////for (unsigned int i = 0; i < boardStates.size(); i++)
            ////{
              ////if (boardStates.at(i).movableTokens.size() > 0)
              ////{
                ////allStatesAreRejected = false;
                ////states.push_back(Node(boardStates.at(i)));
                ////std::cout << boardStates.at(i) << std::endl;
              ////}
              ////else
                ////boardStates.at(i).rejected = true;
            ////}

          //}
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
      startingBoard = new Board(boardWidth, boardHeight);

      // All possible states from an initial board
      std::vector<Board> initialStates = startingBoard->getNextBoards();
      for (unsigned int i = 0; i < initialStates.size(); i++)
      {
        //std::cout << initialStates.at(i);
        //nodes.push_back(Node(initialStates.at(i)));
        addNode(initialStates.at(i));
      }

      //std::cout << *startingBoard << std::endl;
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

    void depthFirstSearch()
    {
      if (solutionFound)
        return;

      Node *currentNode = searchStack.top();
      searchStack.pop();
      currentNode->visited = true;

      std::cout << currentNode->data << std::endl;

      if (currentNode->data.isGoal())
      {
        solutionFound = true;
        std::cout << "FOUND SOLUTION!" << std::endl;
        return;
      }
      else
      {
        // generate new states
        std::vector<Board> boards = currentNode->data.getNextBoards();
        for (unsigned int i = 0; i < boards.size(); i++)
        {
          addNeighborToNode(currentNode, boards.at(i));
        }

        for (unsigned int i = 0; i < currentNode->states.size(); i++)
        {
          searchStack.push(currentNode->states.at(i));
          depthFirstSearch();
        }
      }

      currentNode->visited = false;
    }

    ~Solver()
    {
      delete startingBoard;
      startingBoard = NULL;
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
    Board *startingBoard;
    std::vector<Node> nodes;
    std::stack<Node*> searchStack;
    bool solutionFound;
};

#endif
