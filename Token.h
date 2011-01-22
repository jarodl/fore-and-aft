/*
 * =====================================================================================
 *
 *       Filename:  Token.h
 *
 *    Description:  Object for storing data about a token placed on
 *                  a game board.
 *
 *        Version:  1.0
 *        Created:  01/20/2011 12:16:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jarod Luebbert (), jarodluebbert@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <vector>

class Token
{
  public:
    Token() { }

    Token(char t)
    {
      type = t;
    }

    Token(const Token &cpy)
    {
      type = cpy.getType();
      neighbors = cpy.getNeighbors();
    }

    char getType() const
    {
      return type;
    }

    void setType(const char newType)
    {
      type = newType;
    }

    bool operator==(const Token t) const
    {
      return (type == t.getType());
    }

    bool operator!=(const Token t) const
    {
      return (type != t.getType());
    }

    bool operator==(const char t) const
    {
      return type == t;
    }

    bool operator!=(const char t) const
    {
      return type != t;
    }

    void addNeighbor(Token *t)
    {
      neighbors.push_back(t);
    }

    void removeNeighbor(Token t)
    {
      for (unsigned int i = 0; i < neighbors.size(); i++)
        if (*neighbors.at(i) == t)
          neighbors.erase(neighbors.begin()+i);
    }

    void removeAllNeighbors()
    {
      neighbors.clear();
    }

    bool isAdjacent(Token t)
    {
      for (unsigned int i = 0; i < neighbors.size(); i++)
        if (*neighbors.at(i) == t)
          return true;
      return false;
    }

    std::vector<Token*> getNeighbors() const
    {
      return neighbors;
    }

  private:
    char type;
    std::vector<Token*> neighbors;
};

#endif
