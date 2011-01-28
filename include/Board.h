/*
 * =====================================================================================
 *
 *       Filename:  Board.h
 *
 *    Description:  Wrapper for the string of Board for storing available
 *                  moves.
 *
 *        Version:  1.0
 *        Created:  01/26/2011 10:25:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jarod Luebbert (), jarodluebbert@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef Board_H
#define Board_H

#include <string>
#include <stack>

#include <sstream>

#define UPPER_LEFT 'R'
#define LOWER_RIGHT 'B'
#define OPEN '_'

class Board
{
  public:

    Board()
    {
    }

    Board(int w, int h)
    {
      width = w;
      height = h;

      calculateParams();

      values = "";
      values.resize(size);

      clearValues(UPPER_LEFT, LOWER_RIGHT);
      updateMoves();
    }

    Board(const Board &cpy)
    {
      width = cpy.getWidth();
      height = cpy.getHeight();

      values = cpy.getValues();
      moves = cpy.getMoves();

      size = cpy.getSize();
      cornerWidth = cpy.getCornerWidth();
      cornerSize = cpy.getCornerSize();

      leftLimit = cpy.getLeftLimit();
      rightLimit = cpy.getRightLimit();
      topLimit = cpy.getTopLimit();
      bottomLimit = cpy.getBottomLimit();
    }

    // Function: getCopyAndMakeNextMove
    //
    // Desc: Creates a copy of the current object then performs the makeNextMove
    // function on it, advancing it to its next state.
    //
    // Pre: None.
    //
    // Post: A new object is returned and the next move is taken from the stack.
    Board getCopyAndMakeNextMove()
    {
      Board nextState = Board(*this);

      nextState.makeNextMove();

      return nextState;
    }

    // Function: makeNextMove
    //
    // Desc: Takes the next move from the moves stack and executes it.
    //
    // Pre: None.
    //
    // Post: If there is a move then the values are changed.
    void makeNextMove()
    {
      if (!moves.empty())
        swapOpenValueWithValue(moves.top());
    }

    // Function: movesExist
    //
    // Desc: Determines if there are any moves that can be made from the current
    // open location.
    //
    // Pre: None.
    //
    // Post: Returns true or false depending on if moves exist.
    bool movesExist() const
    {
      return (!moves.empty());
    }

    // Function: getSize
    //
    // Desc: Returns the number of Board.
    //
    // Pre: None.
    //
    // Post: The size of the Board string is returned.
    int getSize() const
    {
      return values.size();
    }


    // Function: getValues
    //
    // Desc: Returns all of the Board as a string.
    //
    // Pre: None.
    //
    // Post: The values are returned.
    std::string getValues() const
    {
      return values;
    }

    std::stack<int> getMoves() const
    {
      return moves;
    }

    int getMiddle() const
    {
      return middle;
    }

    int getLeftLimit() const
    {
      return leftLimit;
    }

    int getRightLimit() const
    {
      return rightLimit;
    }

    int getTopLimit() const
    {
      return topLimit;
    }

    int getBottomLimit() const
    {
      return bottomLimit;
    }

    int getOpenValueIndex() const
    {
      return openValueIndex;
    }

    int getCornerSize() const
    {
      return cornerSize;
    }

    int getCornerWidth() const
    {
      return cornerWidth;
    }

    // Function: getWidth
    //
    // Desc: Returns the width of the Board. Really only used for the copy
    // constructor.
    //
    // Pre: None.
    //
    // Post: The width is returned.
    int getWidth() const
    {
      return width;
    }

    // Function: getHeight
    //
    // Desc: Returns the height of the Board. Really only used for the copy
    // constructor.
    //
    // Pre: None.
    //
    // Post: The height is returned.
    int getHeight() const
    {
      return height;
    }

    // Function: peekAtNextMove
    //
    // Desc: Returns the first move in the moves list without removing it.
    // Returns -1 if there are not any moves to be made.
    //
    // Pre: None.
    //
    // Post: The next move is returned.
    int peekAtNextMove() const
    {
      if (movesExist())
        return moves.top();
      return -1;
    }

    // Function: paramDebugString
    //
    // Desc: Used for debugging, the function returns the current location of
    // the open value and its move limits.
    //
    // Pre: All values should be instantiated.
    //
    // Post: The debug string is returned.
    std::string paramDebugString() const
    {
      std::ostringstream o;
      o << openValueIndex << " " << topLimit << " " << rightLimit << " " << bottomLimit << " " << leftLimit;
      return o.str();
    }

  private:

    // Function: swapOpenValueWithValue
    //
    // Desc: Takes a value and exchanges its place with the `open` value. Since
    // the `open` value's index has changed then we update the information used
    // for determining valid moves.
    //
    // Pre: Assumes that valueToMove is within the bounds of the values array.
    //
    // Post: The openValueIndex is set to valueToMove and valueToMove now
    // resides where the openValueIndex was.
    void swapOpenValueWithValue(int valueToMove)
    {
      values[openValueIndex] = values[valueToMove];
      values[valueToMove] = OPEN;

      setOpenValueIndex(valueToMove);
      updateMoves();
    }

    // Function: setOpenValueIndex
    //
    // Desc: Sets the index of the 'open' piece in the values array. After we
    // update the location of the open value we calculate the top, right, bottom
    // and left bounds. The bounds determine where possible Board are that can
    // move in to the open value.
    //
    // Pre: The function assumes that newOpenValueIndex is the index of the open
    // value in the `values` array.
    //
    // Post: The instance variables leftLimit, rightLimit, topLimit and
    // bottomLimit are calculated based on the index of the open value.
    void setOpenValueIndex(int newOpenValueIndex)
    {
      openValueIndex = newOpenValueIndex;

      int offset = cornerWidth - 1;
      int cornerOffset = (openValueIndex > middle) ? offset : 0;
      bool middleRow = (openValueIndex >= middle - offset &&
          openValueIndex <= middle + offset);

      int y = ((openValueIndex - cornerOffset) / cornerWidth);
      int x = (openValueIndex - cornerOffset - (y * cornerWidth));

      int rightOffset = 0;
      int leftOffset = 0;
      int vertOffset = (cornerWidth * y);

      if (middleRow && openValueIndex <= middle)
        rightOffset = offset;
      if (middleRow && openValueIndex > middle)
        leftOffset = offset;

      leftLimit = openValueIndex - x - leftOffset;
      rightLimit = openValueIndex + (offset - x) + rightOffset;

      topLimit = openValueIndex - vertOffset;
      bottomLimit = openValueIndex + vertOffset;

      if (middleRow && openValueIndex > middle)
        topLimit = openValueIndex;
      else if (middleRow && openValueIndex < middle)
        bottomLimit = openValueIndex;
    }

    // Function: calculateParams
    //
    // Desc: Calculates valuable data that we can use to make moves and
    // determine the parameters easier. The cornerWidth is how wide the upper
    // left and lower right corners are. The cornerSize is how many values are
    // in each corner.
    //
    // Pre: Assumes that the board has been initialized.
    //
    // Post: Valuable data is set for determining valid moves.
    void calculateParams()
    {
      size = (width * height) - ((height - 1) * (width / 2));
      middle = size / 2;
      cornerWidth = (width / 2) + 1;
      cornerSize = cornerWidth * cornerWidth;
    }

    // Function: clearValues
    //
    // Desc:
    //
    // Pre:
    //
    // Post:
    void clearValues(char upperLeft, char lowerRight)
    {
      for (int i = 0; i < size; i++)
      {
        if (i < middle)
          values[i] = upperLeft;
        else if (i > middle)
          values[i] = lowerRight;
        else
        {
          values[i] = OPEN;
          setOpenValueIndex(i);
        }
      }
    }

    // Function: clearMoves
    //
    // Desc:
    //
    // Pre:
    //
    // Post:
    void clearMoves()
    {
      while (!moves.empty())
        moves.pop();
    }

    // Function: updateMoves
    //
    // Desc:
    //
    // Pre:
    //
    // Post:
    void updateMoves()
    {
      clearMoves();

      for (int i = 2; i >= 1; i--)
      {
        if (canMoveDownBy(i))
          moves.push(openValueIndex + (cornerWidth * i));
        if (canMoveRightBy(i))
          moves.push(openValueIndex + i);
        if (canMoveUpBy(i))
          moves.push(openValueIndex - (cornerWidth * i));
        if (canMoveLeftBy(i))
          moves.push(openValueIndex - i);
      }
    }

    bool canMoveUpBy(int amount)
    {
      int i = openValueIndex - (cornerWidth * amount);

      if (i >= topLimit && values[i] == UPPER_LEFT)
        return (amount == 2) ? values[i + cornerWidth] == LOWER_RIGHT : true;

      return false;
    }

    bool canMoveDownBy(int amount)
    {
      int i = openValueIndex + (cornerWidth * amount);

      if (i <= bottomLimit && values[i] == LOWER_RIGHT)
        return (amount == 2) ? values[i - cornerWidth] == UPPER_LEFT : true;

      return false;
    }

    bool canMoveLeftBy(int amount)
    {
      int i = openValueIndex - amount;

      if (i >= leftLimit && values[i] == UPPER_LEFT)
        return (amount == 2) ? values[openValueIndex - 1] == LOWER_RIGHT : true;

      return false;
    }

    bool canMoveRightBy(int amount)
    {
      int i = openValueIndex + amount;

      if (i <= rightLimit && values[i] == LOWER_RIGHT)
        return (amount == 2) ? values[openValueIndex + 1] == UPPER_LEFT : true;

      return false;
    }

  private:
    int width;
    int height;

    int size;
    int middle;

    int cornerWidth;
    int cornerSize;

    int openValueIndex;
    int leftLimit;
    int rightLimit;
    int topLimit;
    int bottomLimit;

    std::string values;
    std::stack<int> moves;
};

#endif
