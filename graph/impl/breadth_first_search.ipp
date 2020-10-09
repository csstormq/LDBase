//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2020, csstormq. Distributed under the BSD 3-Clause License.
// (See accompanying file LICENSE or copy at
// https://github.com/csstormq/LDBase/blob/master/LICENSE)
//
//////////////////////////////////////////////////////////////////////////////
#ifndef LDBASE_GRAPH_IMPL_BREADTH_FIRST_SEARCH_IPP
#define LDBASE_GRAPH_IMPL_BREADTH_FIRST_SEARCH_IPP

#include <list>
#include <queue>
#include <stdexcept>
#include <unordered_map>

namespace LDBase {
namespace graph {

// Single-source and single-goal version
template <typename TGraph, typename TNode>
std::unordered_map<TNode, TNode> BreadthFirstSearch(
    const TGraph& graph, const TNode& start, const TNode& goal)
{
  std::queue<TNode> frontier;
  frontier.push(start);
  std::unordered_map<TNode, TNode> came_from;
  came_from[start] = start;
  while (!frontier.empty())
  {
    const auto& current = std::move(frontier.front());
    frontier.pop();
    if (current == goal)
    {
      return came_from;
    }
    if (graph.HasNeighbors(current))
    {
      for (const auto& next : graph.GetNeighbors(current))
      {
        if (came_from.find(next) == came_from.end())
        {
          frontier.push(next);
          came_from[next] = current;
        }
      }
    }
  }
  return std::unordered_map<TNode, TNode>();
}

// Single-source and multiple-goal version
template <typename TGraph, typename TNode>
std::unordered_map<TNode, TNode> BreadthFirstSearch(
    const TGraph& graph, const TNode& start)
{
  std::queue<TNode> frontier;
  frontier.push(start);
  std::unordered_map<TNode, TNode> came_from;
  came_from[start] = start;
  while (!frontier.empty())
  {
    const auto& current = std::move(frontier.front());
    frontier.pop();
    if (graph.HasNeighbors(current))
    {
      for (const auto& next : graph.GetNeighbors(current))
      {
        if (came_from.find(next) == came_from.end())
        {
          frontier.push(next);
          came_from[next] = current;
        }
      }
    }
  }
  return came_from;
}

template <typename TNode>
bool ReconstructPath(const std::unordered_map<TNode, TNode>& came_from,
    const TNode& start, const TNode& goal, std::list<TNode>& path)
{
  if (came_from.find(goal) == came_from.end())
  {
    return false; // no reachable path exists
  }
  
  TNode current = goal;
  while (current != start)
  {
    path.push_front(current);
    const auto it = came_from.find(current);
    if (it != came_from.end())
    {
      current = it->second;
    }
    else
    {
      throw std::runtime_error("invalid arguments");
    }
  }
  path.push_front(start);
  return true;
}

}   // namespace graph
}   // namespace LDBase

#endif  // LDBASE_GRAPH_IMPL_BREADTH_FIRST_SEARCH_IPP
