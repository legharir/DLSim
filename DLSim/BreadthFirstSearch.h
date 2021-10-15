#pragma once

#include <queue>

#include "Graph.h"

template <typename T>
class BreadthFirstSearch
{
public:
    static hasPath(const Graph<T>& graph, )
    {
    }

private:
    static bfs(const Graph<T>& graph, )
    {
        std::queue<const T&> queue;
        std::unordered_set<T> seenVertices;

        while (!queue.empty())
        {
            const auto curVertex = queue.pop();
            for (const auto& neighbour : graph.getNeighbours(curVertex))
            {

                if (!seenVertices.contains(neighbour))
                {
                }
            }
        }
    }
};
