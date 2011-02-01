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
void Graph<T>::addNeighborToNode(int neighborKey, T neighborValue,
    int sourceKey, T sourceValue)
{
  Node *n = getNodeWithValue(neighborKey, neighborValue);
  Node *m = getNodeWithValue(sourceKey, sourceValue);
  m->neighbors.push_back(n);
}

template <typename T>
void Graph<T>::markNodeVisited(int key, T value)
{
  Node *n = getNodeWithValue(key, value);
  n->visited = true;
}

template <typename T>
typename Graph<T>::Node* Graph<T>::getNode(int key, T value)
{
  return getNodeWithValue(key, value);
}

template <typename T>
typename Graph<T>::Node* Graph<T>::getNodeWithValue(int key, T value)
{
  typename std::map<int, Node *>::iterator itr;
  itr = nodeMap.find(key);

  if (itr == nodeMap.end())
  {
    Node *newNode = new Node(value, key);
    allNodes.push_back(newNode);
    nodeMap.insert(std::pair<int, Node*>(key , newNode));

    return newNode;
  }

  return (*itr).second;
}

template <typename T>
bool Graph<T>::nodeExists(int key)
{
  typename std::map<int, Node*>::iterator itr;
  itr = nodeMap.find(key);

  return (itr != nodeMap.end());
}