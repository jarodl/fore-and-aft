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

class Token
{
  public:
    Token()
    {
    }

    Token(int newX, int newY, char t)
    {
      x = newX;
      y = newY;
      type = t;
    }

    Token(const Token &cpy)
    {
      x = cpy.getX();
      y = cpy.getY();
      type = cpy.getType();
    }

    int getX() const
    {
      return x;
    }

    int getY() const
    {
      return y;
    }

    char getType() const
    {
      return type;
    }

    void setX(const int newX)
    {
      x = newX;
    }

    void setY(const int newY)
    {
      y = newY;
    }

    void setType(const char newType)
    {
      type = newType;
    }

    bool operator==(const char t) const
    {
      return type == t;
    }

    bool operator!=(const char t) const
    {
      return type != t;
    }

  private:
    int x, y;
    char type;
};

#endif
