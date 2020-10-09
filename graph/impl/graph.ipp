//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2020, csstormq. Distributed under the BSD 3-Clause License.
// (See accompanying file LICENSE or copy at
// https://github.com/csstormq/LDBase/blob/master/LICENSE)
//
//////////////////////////////////////////////////////////////////////////////
#ifndef LDBASE_GRAPH_IMPL_GRAPH_IPP
#define LDBASE_GRAPH_IMPL_GRAPH_IPP

namespace LDBase {
namespace graph {

template <typename TNode>
void Graph<TNode>::AddEdge(const TNode& start, const TNode& goal)
{
  graph_[start].push_back(goal);
}

template <typename TNode>
bool Graph<TNode>::HasNeighbors(const TNode& node) const
{
  const auto it = graph_.find(node);
  if (it != graph_.end())
  {
    const auto& neighbors = it->second;
    return !neighbors.empty();
  }
  return false;
}

template <typename TNode>
const typename Graph<TNode>::Neighbors&
Graph<TNode>::GetNeighbors(const TNode& node) const
{
  return graph_.find(node)->second;
}

}   // namespace graph
}   // namespace LDBase

#endif  // LDBASE_GRAPH_IMPL_GRAPH_IPP
