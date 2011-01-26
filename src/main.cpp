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

int main(int argc, char* argv[])
{
  int boardWidth, boardHeight;
  printf("Enter the size of the board in the format (w, h): ");
  scanf("%d, %d", &boardWidth, &boardHeight);


  Board b = Board(boardWidth, boardHeight);
  //while (!b.pieceMoves.empty())
  //{
    //std::cout << b.pieceMoves.top() << std::endl;
    //b.pieceMoves.pop();
  //}
  //std::cout << b << std::endl;

  //b.move(9, 8);
  //while (!b.pieceMoves.empty())
  //{
    //std::cout << b.pieceMoves.top() << std::endl;
    //b.pieceMoves.pop();
  //}
  //std::cout << b << std::endl;

  //b.move(7, 9);
  //while (!b.pieceMoves.empty())
  //{
    //std::cout << b.pieceMoves.top() << std::endl;
    //b.pieceMoves.pop();
  //}
  //std::cout << b << std::endl;

  //b.move(8, 7);
  //while (!b.pieceMoves.empty())
  //{
    //std::cout << b.pieceMoves.top() << std::endl;
    //b.pieceMoves.pop();
  //}
  //std::cout << b << std::endl;
  
  //b.move(10, 8);
  //while (!b.pieceMoves.empty())
  //{
    //std::cout << b.pieceMoves.top() << std::endl;
    //b.pieceMoves.pop();
  //}
  //std::cout << b << std::endl;

  //b.move(13, 10);
  //while (!b.pieceMoves.empty())
  //{
    //std::cout << b.pieceMoves.top() << std::endl;
    //b.pieceMoves.pop();
  //}
  //std::cout << b << std::endl;

  //b.move(20, 13);
  //while (!b.pieceMoves.empty())
  //{
    //std::cout << b.pieceMoves.top() << std::endl;
    //b.pieceMoves.pop();
  //}
  //std::cout << b << std::endl;

  //b.move(21, 20);
  //while (!b.pieceMoves.empty())
  //{
    //std::cout << b.pieceMoves.top() << std::endl;
    //b.pieceMoves.pop();
  //}
  //std::cout << b << std::endl;

  //b.move(22, 21);
  //while (!b.pieceMoves.empty())
  //{
    //std::cout << b.pieceMoves.top() << std::endl;
    //b.pieceMoves.pop();
  //}
  //std::cout << b << std::endl;

  //b.move(30, 22);
  //while (!b.pieceMoves.empty())
  //{
    //std::cout << b.pieceMoves.top() << std::endl;
    //b.pieceMoves.pop();
  //}
  //std::cout << b << std::endl;

  //b.move(27, 30);
  //while (!b.pieceMoves.empty())
  //{
    //std::cout << b.pieceMoves.top() << std::endl;
    //b.pieceMoves.pop();
  //}
  //std::cout << b << std::endl;
  Solver v = Solver(boardWidth, boardHeight);
  v.searchGoalDF();

  return 0;
}
