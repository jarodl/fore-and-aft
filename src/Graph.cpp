/*
 * =====================================================================================
 *
 *       Filename:  Graph.cpp
 *
 *    Description:  Graph implementation.
 *
 *        Version:  1.0
 *        Created:  01/28/2011 14:49:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jarod Luebbert (), jarodluebbert@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

template <typename T>
Graph<T>::Graph()
{
}

template <typename T>
Graph<T>::~Graph()
{
  for (unsigned int i = 0; i < allNodes.size(); i++)
    delete allNodes[i];
}

template <typename T>
void Graph<T>::addNeighborToNode(std::string neighborName, T neighborValue,
    std::string sourceName, T sourceValue)
{
  Node *n = getNodeWithValue(neighborName, neighborValue);
  Node *m = getNodeWithValue(sourceName, sourceValue);
  m->neighbors.push_back(n);
}

template <typename T>
void Graph<T>::markNodeVisited(std::string name, T value)
{
  Node *n = getNodeWithValue(name, value);
  n->visited = true;
}

template <typename T>
typename Graph<T>::Node* Graph<T>::getNode(std::string name, T value)
{
  return getNodeWithValue(name, value);
}

template <typename T>
typename Graph<T>::Node* Graph<T>::getNodeWithValue(std::string name, T value)
{
  typename std::map<std::string, Node *>::iterator itr;
  itr = nodeMap.find(name);

  if (itr == nodeMap.end())
  {
    Node *newNode = new Node(value);
    allNodes.push_back(newNode);
    nodeMap.insert(std::pair<std::string, Node*>(name, newNode));
    return newNode;
  }

  return (*itr).second;
}
