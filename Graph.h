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

template <typename T>
class Graph
{
  private:
    struct Node
    {
      T data;
      std::vector<Node*> neighbors;
    };

  public:
    Graph()
    {
    }

    ~Graph()
    {
    }

    //bool adjacent(T *x, T *y)
    //{
      //// need to check if both nodes are in the graph
      ////for (unsigned int i = 0; i < x->neighbors.size(); i++)
        ////if (x->neighbors.at(i)->data == y)
          ////return true;

      //return false;
    //}

    //void addEdge(T *x, T *y)
    //{
      //x->neighbors.push_back(y);
      //y->neighbors.push_back(x);
    //}

    //void removeEdge(T *x, T *y)
    //{
      //if (adjacent(x, y))
      //{
      //}
    //}

    void add(T *x)
    {
      //Node *n = new Node();
      //n->data = *x;
      //nodes.push_back(n);
    }

    void remove(T *x)
    {
      //for (unsigned int i = 0; i < nodes.size(); i++)
        //if (nodes.at(i)->data == x)
          //nodes.erase(i);
    }

  private:
    std::vector<Node*> nodes;
};

#endif
