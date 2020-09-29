//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2020, csstormq. Distributed under the BSD 3-Clause License.
// (See accompanying file LICENSE or copy at
// https://github.com/csstormq/LDBase/blob/master/LICENSE)
//
//////////////////////////////////////////////////////////////////////////////
#ifndef LDBASE_GRAPH_GRAPH_HPP
#define LDBASE_GRAPH_GRAPH_HPP

#include <list>
#include <unordered_map>

namespace LDBase {
namespace graph {

template <typename TNode>
class Graph
{
public:
  Graph() = default;
  ~Graph() = default;

  /**
   * @brief Set a directed edge from A to B, meaning that A can arrive to B
   *        but not vice versa.
   * @param A The node where the edge starts.
   * @param B The node that the edge points to.
   */
  void AddEdge(const TNode& A, const TNode& B);

  /**
   * @brief Find a shortest path between two nodes by the number of
   *        relationships (i.e., hops) between them. (I write “a shortest path”
   *        because there are often multiple equivalently-short paths.)
   * @param from The start node of pathfinding.
   * @param to The target node of pathfinding.
   * @return On success, returns a shortest path that contains all nodes
   *         to go through. The first is start node, the end is target node.
   *         On error, an empty path is returned, meaning that no reachable
   *         path exists between them.
   */
  std::list<TNode> FindShortestPathByHops(const TNode& from, const TNode& to);

private:
  std::list<TNode> BreadthFirstSearch(const TNode& from, const TNode& to);
  std::list<TNode> BreadthFirstSearchImpl2(const TNode& from, const TNode& to);

private:
  typedef TNode FromNode;
  typedef std::list<TNode> ToNodes;
  std::unordered_map<FromNode, ToNodes> graph_;
};

}   // namespace graph
}   // namespace LDBase

#include "LDBase/graph/impl/graph.ipp"

#endif  // LDBASE_GRAPH_GRAPH_HPP
