/*
 * =====================================================================================
 *
 *       Filename:  Graph.h
 *
 *    Description:  
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

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

template <typename Type>
class Graph
{
  private:
    class Node
    {
      public:
        Node()
        {
        }

        Type getValue() const
        {
          return value;
        }

        void setValue(const Type v)
        {
          value = v;
        }

        friend std::ostream& operator>> (std::istream& input,
            Node& n)
        {
          Type v;
          input >> v;
          n.setValue(v);

          return input;
        }

        friend std::ostream& operator<< (std::ostream& output,
            const Node& n)
        {
          output << n.getValue();
          return output;
        }

      private:
        Type value;
        std::vector<Node> neighbors;
    };

  public:
    Graph()
    {
    }

    ~Graph()
    {
    }

    bool isAdjacent(Type *x, Type *y)
    {
      return true;
    }

    friend std::ostream& operator<< (std::ostream& output,
        const Graph<Type>& g)
    {
      for (int i = 0; i < 5; i++)
        output << " ";
        
      return output;
    }

    //bool isAdjacent(Node *x, Node *y);
    //bool neighborsFor(Node *x);
    //void addEdge(Node *x, Node *y);
    //void removeEdge(Node *from, Node *to);

  private:
    std::vector<Node> nodes;
};

#endif
