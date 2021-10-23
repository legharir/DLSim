// Adjacency representation of a undirected graph.

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <QDebug>

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
    }

    const std::unordered_set<T>& getNeighbours(T v) const
    {
        return m_adj.at(v);
    }

    auto begin() const
    {
        return m_adj.begin();
    }

    auto end() const
    {
        return m_adj.end();
    }

    void print() const
    {
        for (const auto& [vertex, neighbours] : m_adj)
        {
            QString neighboursStr;

            for (const auto& neighbour : neighbours)
            {
                neighboursStr.push_back(QString::fromStdString(neighbour->getName()));
                neighboursStr.push_back(QString::fromStdString(", "));
            }

            qDebug() << QString::fromStdString(vertex->getName()) << ":"
                     << "[" << neighboursStr << "]";
        }
    }

private:
    std::unordered_map<T, std::unordered_set<T>> m_adj;
};
