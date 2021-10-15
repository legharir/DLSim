// Adjacency representation of a undirected graph.

#pragma once

#include <set>
#include <unordered_map>
#include <vector>

template <typename T>
class Graph
{
public:
    void addVertex(T v)
    {
        m_adj.insert({ v, {} });
    }

    void removeVertex(T v)
    {
        for (const auto& connectedVertex : m_adj[v])
        {
            m_adj[connectedVertex].erase(v);
        }

        m_adj.erase(v);
    }

    void addEdge(T source, T dest)
    {
        m_adj[source].insert(dest);
        m_adj[dest].insert(source);
    }

    std::set<T> getNeighbours(T v) const
    {
        return m_adj[v];
    }

    auto begin() const
    {
        return m_adj.begin();
    }

    auto end() const
    {
        return m_adj.end();
    }

private:
    std::unordered_map<T, std::set<T>> m_adj;
};
