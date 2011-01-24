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
#include "Solver.h"
#include "Board.h"

int main(int argc, char* argv[])
{
  int boardWidth, boardHeight;
  printf("Enter the size of the board in the format (w, h): ");
  scanf("%d, %d", &boardWidth, &boardHeight);

  //Board b = Board(boardWidth, boardHeight);
  //std::cout << b << std::endl;
  //b.move(13, 12);
  //std::cout << b << std::endl;
  //b.move(18, 13);
  //std::cout << b << std::endl;
  Solver v = Solver(boardWidth, boardHeight);
  v.searchGoalDF();

  return 0;
}
