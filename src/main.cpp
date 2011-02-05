/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Driver for the fore-and-aft puzzle solver.
 *
 *        Version:  1.0
 *        Created:  01/18/2011 20:26:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jarod Luebbert (), jarodluebbert@gmail.com
 *        Company:  
 *
 * =====================================================================================
 * 
 * Performance Information
 *
 *    Depth First Search Performance:
 *
 *      5X5 runs in 0.01 seconds, expands 483 nodes and has 50 nodes in the
 *      solution path.
 *      
 *      7X7 runs in 0.22 seconds, expands 13,074 nodes and has 133 nodes in the
 *      solution path.
 *
 *      9X9 runs in 29.02 seconds, expands 2,063,792 nodes and has 269 nodes in
 *      the solution path.
 *
 *    Breadth First Search Performance:
 *
 *      5X5 runs in 3.84 seconds, expands 133,665 nodes.
 *
 *      For BFS, the way I was recording the traversed path did not work
 *      correctly so I took it out. :(
 *
 * =====================================================================================
*/

#include <iostream>
#include <fstream>

#include "../include/Solver.h"
#include "../include/Board.h"

#define DFS_OUTPUT "dfs.out"
#define BFS_OUTPUT "bfs.out"

void displayMenu(std::ostream &out);
int getBoardSize(std::ostream &out);

// Function: main
//
// Desc: Starting point for a the fore and aft solver. Displays a menu and gets
// the board size then solves the puzzle.
//
// Pre: None.
//
// Post: A board is solved or the program is quit.
int main(int argc, char* argv[])
{
  char userChoice = ' ';
  int boardSize;
  Board puzzle;
  Solver solver;
  std::ofstream fout;

  while (true)
  {
    displayMenu(std::cout);
    std::cin >> userChoice;

    switch(userChoice)
    {
      case '4':
      case 'Q':
      case 'q':
        return 0;
        break;
      case '1':
        boardSize = getBoardSize(std::cout);
        puzzle = Board(boardSize, boardSize);

        solver = Solver(puzzle);
        solver.depthFirstSearch();
        std::cout << solver;

        fout.open(DFS_OUTPUT);
        solver.outputSolution(fout);
        fout.close();
        break;
      case '2':
        boardSize = getBoardSize(std::cout);
        puzzle = Board(boardSize, boardSize);

        solver = Solver(puzzle);
        solver.breadthFirstSearch();
        std::cout << solver;

        fout.open(BFS_OUTPUT);
        solver.outputSolution(fout);
        fout.close();
        break;
      case '3':
        std::cout << std::endl << "BRB, not yet implemented." << std::endl;
        break;
    }
  }

  return 0;
}

// Function: displayMenu
//
// Desc: Displays a menu to the user of available searches to perform.
//
// Pre: None.
//
// Post: Menu is displayed to the output stream.
void displayMenu(std::ostream &out)
{
  out << std::endl
      << "1. Depth-First Search" << std::endl
      << "2. Breadth-First Search" << std::endl
      << "3. Heauristic Search" << std::endl
      << "4. Quit" << std::endl << std::endl;
}

// Function: getBoardSize
//
// Desc: Returns the board size and makes sure it is an odd number.
//
// Pre: None.
//
// Post: An odd board size is returned.
int getBoardSize(std::ostream &out)
{
  int boardSize;

  out << std::endl << "Enter the width of your board: ";
  scanf("%d", &boardSize);
  boardSize = (boardSize % 2 == 0) ? boardSize - 1 : boardSize;

  return boardSize;
}
