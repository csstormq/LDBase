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
  typedef std::list<TNode> Neighbors;

  Graph() = default;
  ~Graph() = default;

  /**
   * @brief Set a directed edge from "start" to "goal", meaning that "start"
   *        can arrive to "goal" but not vice versa.
   * @param start The node where the edge starts.
   * @param goal The node that the edge points to.
   */
  void AddEdge(const TNode& start, const TNode& goal);

  /**
   * @brief Check whether a node has any neighbor.
   * @param node Node identifier.
   * @return Returns true if the node has any neighbor, otherwise false.
   */
  bool HasNeighbors(const TNode& node) const;

  /**
   * @brief Get the const-reference to neighbors of a node.
   *        You must guarantee that neighbors exist before calling this funciton.
   * @param node Node identifier.
   * @return Returns the const-reference to neighbors of the node.
   */
  const Neighbors& GetNeighbors(const TNode& node) const;

private:
  std::unordered_map<TNode, Neighbors> graph_;
};

}   // namespace graph
}   // namespace LDBase

#include "LDBase/graph/impl/graph.ipp"

#endif  // LDBASE_GRAPH_GRAPH_HPP
