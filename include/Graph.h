/*
 * =====================================================================================
 *
 *       Filename:  Graph.h
 *
 *    Description:  Graph definition.
 *
 *        Version:  1.0
 *        Created:  01/27/2011 23:50:46
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

#include <map>
#include <vector>
#include <string>

template <typename T>
class Graph
{
  protected:
    struct Node
    {
      Node(T d, int k) : data(d)
      {
        visited = false;
        key = k;
      }

      std::vector<Node *> neighbors;
      T data;
      int key;
      bool visited;
    };

    std::map<int, Node *> nodeMap;
    bool nodeExists(int key);

  public:
    Graph();
    ~Graph();
    void addNeighborToNode(int neighborKey, T neighborValue,
        int sourceKey, T sourceValue);
    Node* getNode(int key, T value);

};

#include "../src/Graph.cpp"

#endif
