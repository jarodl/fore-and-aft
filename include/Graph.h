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
      Node(T d) : data(d)
      {
        visited = false;
      }

      std::vector<Node *> neighbors;
      T data;

      bool visited;
    };

    std::map<std::string, Node *> nodeMap;
    std::vector<Node *> allNodes;

  private:
    Node* getNodeWithValue(std::string name, T value);

  public:
    Graph();
    ~Graph();
    void addNeighborToNode(std::string neighborName, T neighborValue,
        std::string sourceName, T sourceValue);
    void markNodeVisited(std::string name, T value);
    Node* getNode(std::string name, T value);
};

#include "../src/Graph.cpp"

#endif
