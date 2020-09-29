//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2020, csstormq. Distributed under the BSD 3-Clause License.
// (See accompanying file LICENSE or copy at
// https://github.com/csstormq/LDBase/blob/master/LICENSE)
//
//////////////////////////////////////////////////////////////////////////////
#ifndef LDBASE_GRAPH_GRAPH_IMPL_IPP
#define LDBASE_GRAPH_GRAPH_IMPL_IPP

#include <list>
#include <queue>
#include <stdexcept>
#include <unordered_map>

namespace LDBase {
namespace graph {

template <typename TKey>
class ColorMap
{
public:
  bool IsVisited(const TKey& val) const
  {
    const auto it = color_map_.find(val);
    if (it != color_map_.end())
    {
      return it->second;
    }
    return false;
  }

  void SetVisited(const TKey& val)
  {
    color_map_[val] = true;
  }

private:
  std::unordered_map<TKey, bool> color_map_;
};


template <typename TNode>
void Graph<TNode>::AddEdge(const TNode& A, const TNode& B)
{
  graph_[A].push_back(B);
}

template <typename TNode>
std::list<TNode> Graph<TNode>::FindShortestPathByHops(const TNode& from,
    const TNode& to)
{
  return BreadthFirstSearch(from, to);
}

template <typename TNode>
std::list<TNode> Graph<TNode>::BreadthFirstSearch(const TNode& from,
    const TNode& to)
{
  bool found = false;
  std::queue<TNode> frontier;
  std::unordered_map<TNode, TNode> came_from;
  frontier.push(from);
  came_from[from] = from;
  while (!frontier.empty())
  {
    const auto current = std::move(frontier.front());
    frontier.pop();
    if (current == to)
    {
      found = true;
      break;
    }
    for (const auto& next : graph_[current])
    {
      if (came_from.find(next) == came_from.end())
      {
        frontier.push(next);
        came_from[next] = current;
      }
    }
  }
  if (!found)
  {
    return std::list<TNode>();
  }

  std::list<TNode> path;
  TNode prev = to;
  while (prev != from)
  {
    path.push_front(prev);
    const auto it = came_from.find(prev);
    if (it != came_from.end())
    {
      prev = it->second;
    }
    else
    {
      throw std::runtime_error("BFS impl error");
    }
  }
  path.push_front(from);
  return path;
}

template <typename TNode>
std::list<TNode> Graph<TNode>::BreadthFirstSearchImpl2(const TNode& from,
    const TNode& to)
{
  typedef std::list<TNode> Path;
  Path path;
  std::queue<Path> queue_helper;
  ColorMap<TNode> color_map;

  path.push_back(from);
  queue_helper.push(path);
  color_map.SetVisited(from);
  while (!queue_helper.empty())
  {
    path = std::move(queue_helper.front());
    queue_helper.pop();
    const auto& last = path.back();
    if (last == to)
    {
      return path;
    }
    for (const auto& reachable_node : graph_[last])
    {
      if (!color_map.IsVisited(reachable_node))
      {
        Path new_path(path);
        new_path.push_back(reachable_node);
        queue_helper.push(std::move(new_path));
        color_map.SetVisited(reachable_node);
      }
    }
  }

  return Path();
}

}   // namespace graph
}   // namespace LDBase

#endif  // LDBASE_GRAPH_GRAPH_IMPL_IPP
