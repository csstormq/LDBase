//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2020, csstormq. Distributed under the BSD 3-Clause License.
// (See accompanying file LICENSE or copy at
// https://github.com/csstormq/LDBase/blob/master/LICENSE)
//
//////////////////////////////////////////////////////////////////////////////
#ifndef LDBASE_GRAPH_BREADTH_FIRST_SEARCH_HPP
#define LDBASE_GRAPH_BREADTH_FIRST_SEARCH_HPP

#include <list>
#include <unordered_map>
#include "LDBase/graph/impl/breadth_first_search.ipp"

namespace LDBase {
namespace graph {

/**
 * @brief Find a shortest path between two nodes by the number of
 *        relationships (i.e., hops) between them. (I write “a shortest path”
 *        because there are often multiple equivalently-short paths.)
 * @param start The start node of pathfinding.
 * @param goal The target node of pathfinding.
 * @param path On success, returns a shortest path that contains all nodes
 *         to go through. The first is start node, the end is target node.
 *         On error, an empty path is returned, meaning that no reachable
 *         path exists between them.
 */
template <typename TGraph, typename TNode>
void FindShortestPathByHops(const TGraph& graph, const TNode& start,
    const TNode& goal, std::list<TNode>& path)
{
  const auto came_from = BreadthFirstSearch(graph, start, goal);
  if (!came_from.empty())
  {
    ReconstructPath(came_from, start, goal, path);
  }
}



}   // namespace graph
}   // namespace LDBase

#endif  // LDBASE_GRAPH_BREADTH_FIRST_SEARCH_HPP
