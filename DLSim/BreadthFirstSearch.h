#pragma once

#include <queue>
#include <unordered_map>

#include "Graph.h"

template <typename T>
class BreadthFirstSearch
{
public:
    BreadthFirstSearch(const Graph<T>& graph, T sourceVertex);

    bool hasPathTo(T vertex);

private:
    std::unordered_map<T, T> m_pathTo;
};

template <typename T>
inline BreadthFirstSearch<T>::BreadthFirstSearch(const Graph<T>& graph, T sourceVertex)
{
    std::queue<T> queue;
    queue.push(sourceVertex);

    std::unordered_set<T> seen = { sourceVertex };

    while (!queue.empty())
    {
        const auto& curVertex = queue.front();
        for (const auto& neighbour : graph.getNeighbours(curVertex))
        {
            if (!seen.contains(neighbour))
            {
                m_pathTo[neighbour] = curVertex;
                queue.push(neighbour);
            }
        }

        seen.insert(curVertex);
        queue.pop();
    }
}

template <typename T>
inline bool BreadthFirstSearch<T>::hasPathTo(T vertex)
{
    return m_pathTo.contains(vertex);
}
