#pragma once

#include <queue>
#include <unordered_set>

#include "Graph.h"

class GraphTools
{
public:
    template <typename Vertex>
    static bool doesPathExist(const Graph<Vertex>& graph, Vertex source, Vertex dest)
    {
        return bfs(graph, source, dest);
    }

    template <typename Vertex>
    static bool bfs(const Graph<Vertex>& graph, Vertex source, Vertex dest)
    {
        if (source == dest)
        {
            return true;
        }

        std::queue<Vertex> vertexQueue;
        for (const auto& neighbourVertex : graph.getNeighbours(source))
        {
            vertexQueue.push(neighbourVertex);
        }

        std::unordered_set<Vertex> visited = { source };
        while (!vertexQueue.empty())
        {
            const auto& vertex = vertexQueue.back();

            if (vertexQueue.hasNeighbour())

                visited.insert(vertex);
            vertexQueue.pop();
        }
    }
};
