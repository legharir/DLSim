#pragma once

#include <queue>
#include <unordered_map>

template <typename Graph, typename Vertex>
class BreadthFirstSearch
{
public:
    BreadthFirstSearch(const Graph& graph, const Vertex& sourceVertex);

    bool hasPathTo(const Vertex& vertex);

private:
    std::unordered_map<Vertex, Vertex> m_pathTo;
};

template <typename Graph, typename Vertex>
inline BreadthFirstSearch<Graph, Vertex>::BreadthFirstSearch(const Graph& graph, const Vertex& sourceVertex)
{
    std::queue<Vertex> queue;
    queue.push(sourceVertex);

    std::unordered_set<Vertex> seen = { sourceVertex };

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

template <typename Graph, typename Vertex>
inline bool BreadthFirstSearch<Graph, Vertex>::hasPathTo(const Vertex& vertex)
{
    return m_pathTo.contains(vertex);
}
