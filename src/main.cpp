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
 */

#include <iostream>
#include "../include/Solver.h"
#include "../include/Board.h"
#include "../include/GLBoard.h"

int main(int argc, char* argv[])
{
  int boardWidth, boardHeight;
  printf("Enter the size of the board in the format (w, h): ");
  scanf("%d, %d", &boardWidth, &boardHeight);

  Board b = Board(boardWidth, boardHeight);
  Solver v = Solver(b);

  v.breadthFirstSearch();
  //v.depthFirstSearch();
  //v.nonRecursiveDFS();

  //GLBoard *b = new GLBoard(argc, argv);
  //b->setInstance(b);

  return 0;
}
