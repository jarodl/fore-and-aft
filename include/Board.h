/*
 * =====================================================================================
 *
 *       Filename:  Board.h
 *
 *    Description:  Stores values on a board and moves them around.
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
#define INVALID 'X'

class Board
{
  public:

    // Function: Board
    //
    // Desc:
    //
    // Pre:
    //
    // Post: 
    Board()
    {
    }

    // Function: Board
    //
    // Desc:
    //
    // Pre:
    //
    // Post: 
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

    // Function: Board
    //
    // Desc:
    //
    // Pre:
    //
    // Post: 
    Board(const Board &cpy)
    {
      width = cpy.getWidth();
      height = cpy.getHeight();

      size = cpy.getSize();
      middle = cpy.getMiddle();
      cornerWidth = cpy.getCornerWidth();
      offset = cpy.getOffset();

      openValueIndex = cpy.getOpenValueIndex();
      leftLimit = cpy.getLeftLimit();
      rightLimit = cpy.getRightLimit();
      topLimit = cpy.getTopLimit();
      bottomLimit = cpy.getBottomLimit();

      values = cpy.getValues();

      moves = cpy.getMoves();
    }

    // Function: Board
    //
    // Desc:
    //
    // Pre:
    //
    // Post: 
    ~Board()
    {
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
      moves.pop();

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
      return size;
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

    // Function: getMoves
    //
    // Desc: Returns the stack of moves available on the board.
    //
    // Pre: None.
    //
    // Post: Returns all moves available.
    std::stack<int> getMoves() const
    {
      return moves;
    }

    // Function: getMiddle
    //
    // Desc: Returns the index of the middle of the board. This is where the
    // open location first starts.
    //
    // Pre: The size of the board must be decided.
    //
    // Post: The middle index is returned.
    int getMiddle() const
    {
      return middle;
    }

    // Function: getLeftLimit
    //
    // Desc: Returns the index of the furthest spot left on the board based on
    // where the open location is.
    //
    // Pre: None.
    //
    // Post: The left limit is returned.
    int getLeftLimit() const
    {
      return leftLimit;
    }

    // Function: getRightLimit
    //
    // Desc: Returns the index of the furthest spot right on the board.
    //
    // Pre: None.
    //
    // Post: The right limit is returned.
    int getRightLimit() const
    {
      return rightLimit;
    }

    // Function: getTopLimit
    //
    // Desc: Returns the index of the highest spot on the board.
    //
    // Pre: None.
    //
    // Post: The top limit is returned.
    int getTopLimit() const
    {
      return topLimit;
    }

    // Function: getBottomLimit
    //
    // Desc: Returns the index of the spot that is the lowest on the board.
    //
    // Pre: None.
    //
    // Post: The bottom limit is returned.
    int getBottomLimit() const
    {
      return bottomLimit;
    }

    // Function: getOpenValueIndex
    //
    // Desc: Returns the current index of the open value.
    //
    // Pre: None.
    //
    // Post: The index of the open value is returned.
    int getOpenValueIndex() const
    {
      return openValueIndex;
    }

    // Function: getCornerWidth
    //
    // Desc: Returns the width of the upper left and lower right corners.
    //
    // Pre: The size of the board must be known.
    //
    // Post: The corner width is returned.
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

    // Function: getOffset
    //
    // Desc:
    //
    // Pre:
    //
    // Post:
    int getOffset() const
    {
      return offset;
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

    // Function: ==
    //
    // Desc: Compares two value strings for equality.
    //
    // Pre: None.
    //
    // Post: Returns true if strings are equal, false otherwise.
    bool operator==(const Board &b) const
    {
      if (openValueIndex != b.getOpenValueIndex())
        return false;
      return values == b.getValues();
    }

    // Function: !=
    //
    // Desc: Returns the opposite of ==.
    //
    // Pre: None.
    //
    // Post: Returns true if the values are not equal.
    bool operator!=(const Board &b) const
    {
      return !(*this == b);
    }

    // Function: <<
    //
    // Desc: Overloads the output operator for displaying a board.
    //
    // Pre: None.
    //
    // Post: Displays the board.
    friend std::ostream& operator<<(std::ostream& out, const Board& b)
    {
      std::string values = b.getValues();
      int x;
      int width = b.getCornerWidth();

      for (int i = 0; i < b.getMiddle(); i++)
      {
        x = (i - ((i / width) * width));

        out << values[i] << " ";

        if (x == width - 1)
        {
          for (int j = 0; j < width - 1; j++)
            out << INVALID << " ";
          out << std::endl;
        }
      }
      
      for (int i = b.getMiddle(); i < b.getMiddle() + width; i++)
        out << values[i] << " ";
      out << std::endl;

      for (int i = 0; i < b.getHeight() / 2; i++)
      {
        for (int j = 0; j < width - 1; j++)
          out << INVALID << " ";

        int start = b.getMiddle() + ((i + 1) * width);
        for (int j = start; j < start + width; j++)
          out << values[j] << " ";
        out << std::endl;
      }

      return out;
    }

    // Function: clearValues
    //
    // Desc: Resets the values to their starting values.
    //
    // Pre: None.
    //
    // Post: All values on the board have their default setting and locations.
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
    inline
    void setOpenValueIndex(int newOpenValueIndex)
    {
      openValueIndex = newOpenValueIndex;

      if (openValueIndex < middle - offset)
      {
        int y = openValueIndex / cornerWidth;
        int x = openValueIndex - (y * cornerWidth);
        if (x == offset)
          bottomLimit = openValueIndex + (cornerWidth * ((offset - y) + offset));
        else
          bottomLimit = openValueIndex + (cornerWidth * (offset - y));
        topLimit = x;

        leftLimit = openValueIndex - x;
        rightLimit = openValueIndex + (offset - x);
        return;
      }
      else if (openValueIndex > middle + offset)
      {
        int y = (openValueIndex - offset) / cornerWidth;
        int x = openValueIndex - offset - (y * cornerWidth);
        y = y - offset;
        if (x == 0)
          topLimit = openValueIndex - (y * cornerWidth) - (cornerWidth * offset);
        else
          topLimit = openValueIndex - (y * cornerWidth);
        bottomLimit = openValueIndex + (cornerWidth * (offset - y));

        leftLimit = openValueIndex - x;
        rightLimit = openValueIndex + (offset - x);
        return;
      }
      else if (openValueIndex > middle)
      {
        int y = (openValueIndex - offset) / cornerWidth;
        int x = openValueIndex - offset - (y * cornerWidth);
        y = y - offset;
        topLimit = openValueIndex;
        bottomLimit = openValueIndex + openValueIndex + (cornerWidth * (offset - y));
        leftLimit = openValueIndex - x - offset;
        rightLimit = openValueIndex + (offset - x);
        return;
      }
      else if (openValueIndex < middle)
      {
        int y = openValueIndex / cornerWidth;
        int x = openValueIndex - (y * cornerWidth);
        topLimit = x;
        bottomLimit = openValueIndex;
        leftLimit = openValueIndex - x;
        rightLimit = openValueIndex + (offset - x) + offset;
        return;
      }
      else
      {
        int y = openValueIndex / cornerWidth;
        int x = openValueIndex - (y * cornerWidth);
        topLimit = x;
        bottomLimit = openValueIndex + (cornerWidth * y);
        leftLimit = openValueIndex - x;
        rightLimit = openValueIndex + (offset - x) + offset;
        return;
      }
    }

    // Function: calculateParams
    //
    // Desc: Calculates valuable data that we can use to make moves and
    // determine the parameters easier. The cornerWidth is how wide the upper
    // left and lower right corners are.
    //
    // Pre: Assumes that the board has been initialized.
    //
    // Post: Valuable data is set for determining valid moves.
    inline
    void calculateParams()
    {
      offset = width / 2;
      size = (width * height) - ((height - 1) * offset);
      middle = size / 2;
      cornerWidth = offset + 1;
    }

    // Function: clearMoves
    //
    // Desc: Empties the moves stack of available moves.
    //
    // Pre: None.
    //
    // Post: The moves stack is emptied.
    void clearMoves()
    {
      moves = std::stack<int>();
    }

    // Function: updateMoves
    //
    // Desc: Looks around the open location for available moves and adds them to
    // the stack.
    //
    // Pre: None.
    //
    // Post: Old moves are cleared and the available moves are added to the
    // moves stack.
    void updateMoves()
    {
      clearMoves();

      int left = openValueIndex - 1;
      int right = openValueIndex + 1;
      int up = openValueIndex - cornerWidth;
      int down = openValueIndex + cornerWidth;

      if (canMoveDownOneTo(down))
        moves.push(down);
      if (canMoveRightOneTo(right))
        moves.push(right);
      if (canMoveUpOneTo(up))
        moves.push(up);
      if (canMoveLeftOneTo(left))
        moves.push(left);

      left = left - 1;
      right = right + 1;
      up = up - cornerWidth;
      down = down + cornerWidth;

      if (canMoveDownTwoTo(down))
        moves.push(down);
      if (canMoveRightTwoTo(right))
        moves.push(right);
      if (canMoveUpTwoTo(up))
        moves.push(up);
      if (canMoveLeftTwoTo(left))
        moves.push(left);
    }

    // Function: canMoveUpBy
    //
    // Desc: Determines if the open location can move up by a certain amount.
    //
    // Pre: None.
    //
    // Post: Returns true if a move exists.
    inline
    bool canMoveUpOneTo(int pos)
    {
      return (pos >= topLimit && values[pos] == UPPER_LEFT);
    }

    // Function: Board
    //
    // Desc:
    //
    // Pre:
    //
    // Post: 
    inline
    bool canMoveUpTwoTo(int pos)
    {
      return (pos >= topLimit && values[pos] == UPPER_LEFT &&
          values[pos + cornerWidth] == LOWER_RIGHT);
    }

    // Function: canMoveDownBy
    //
    // Desc: Determines if the open location can move down by a certain amount.
    //
    // Pre: None.
    //
    // Post: Returns true if a move exists.
    inline
    bool canMoveDownOneTo(int pos)
    {
      return (pos <= bottomLimit && values[pos] == LOWER_RIGHT);
    }

    // Function: Board
    //
    // Desc:
    //
    // Pre:
    //
    // Post: 
    inline
    bool canMoveDownTwoTo(int pos)
    {
      return (pos <= bottomLimit && values[pos] == LOWER_RIGHT &&
          values[pos - cornerWidth] == UPPER_LEFT);
    }

    // Function: canMoveLeftBy
    //
    // Desc: Determines if the open location can move left by a certain amount.
    //
    // Pre: None.
    //
    // Post: Returns true if a move exists.
    inline
    bool canMoveLeftOneTo(int pos)
    {
      return (pos >= leftLimit && values[pos] == UPPER_LEFT);
    }

    // Function: Board
    //
    // Desc:
    //
    // Pre:
    //
    // Post: 
    inline
    bool canMoveLeftTwoTo(int pos)
    {
      return (pos >= leftLimit && values[pos] == UPPER_LEFT &&
          values[pos + 1] == LOWER_RIGHT);
    }

    // Function: canMoveRightBy
    //
    // Desc: Determines if the open location can move right by a certain amount.
    //
    // Pre: None.
    //
    // Post: Returns true if a move exists.
    inline
    bool canMoveRightOneTo(int pos)
    {
      return (pos <= rightLimit && values[pos] == LOWER_RIGHT);
    }

    // Function: Board
    //
    // Desc:
    //
    // Pre:
    //
    // Post: 
    inline
    bool canMoveRightTwoTo(int pos)
    {
      return (pos <= rightLimit && values[pos] == LOWER_RIGHT &&
          values[pos - 1] == UPPER_LEFT);
    }

  private:
    int width;
    int height;

    int size;
    int middle;
    int cornerWidth;
    int offset;

    int openValueIndex;
    int leftLimit;
    int rightLimit;
    int topLimit;
    int bottomLimit;

    std::string values;
    std::stack<int> moves;
};

#endif
