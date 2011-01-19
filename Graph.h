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
#include <string>

class Graph
{
  private:
    struct node
    {
      std::string value;
      std::vector<node> adj_list;
    };

  public:
    Graph();
    bool isAdjacent(node *x, node *y);
    bool neighborsFor(node *x);
    void addEdge(node *x, node *y);
    void removeEdge(node *from, node *to);
    std::string getNodeValue(node *x);
    void setNodeValue(node *x, std::string v);

  private:
    std::vector<node> nodes;
};

#endif
