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

// Function: Graph
//
// Desc:
//
// Pre:
//
// Post: 
template <typename T>
Graph<T>::Graph()
{
}

// Function: ~Graph
//
// Desc:
//
// Pre:
//
// Post: 
template <typename T>
Graph<T>::~Graph()
{
  typename std::map<int, Node*>::iterator itr;
  for (itr = nodeMap.begin(); itr != nodeMap.end(); itr++)
    delete (*itr).second;
}

// Function: addNeighborToNode
//
// Desc:
//
// Pre:
//
// Post: 
template <typename T>
void Graph<T>::addNeighborToNode(int neighborKey, T neighborValue,
    int sourceKey, T sourceValue)
{
  Node *n = getNode(neighborKey, neighborValue);
  Node *m = getNode(sourceKey, sourceValue);
  m->neighbors.push_back(n);
}

// Function: getNode
//
// Desc:
//
// Pre:
//
// Post: 
template <typename T>
typename Graph<T>::Node* Graph<T>::getNode(int key, T value)
{
  typename std::map<int, Node *>::iterator itr;
  itr = nodeMap.find(key);

  if (itr == nodeMap.end())
  {
    Node *newNode = new Node(value, key);
    nodeMap.insert(std::pair<int, Node*>(key , newNode));

    return newNode;
  }

  return (*itr).second;
}

// Function: nodeExists
//
// Desc:
//
// Pre:
//
// Post: 
template <typename T>
bool Graph<T>::nodeExists(int key)
{
  typename std::map<int, Node*>::iterator itr;
  itr = nodeMap.find(key);

  return (itr != nodeMap.end());
}
