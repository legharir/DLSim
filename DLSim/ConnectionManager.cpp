#include "ConnectionManager.h"

#include <QDebug>

#include "STLTools.h"

#include "BreadthFirstSearch.h"
#include "ElectronicComponent.h"
#include "Terminal.h"

void ConnectionManager::removeComponent(const ElectronicComponent* component)
{
    for (const auto& terminal : component->getTerminals())
    {
        m_connections.erase(terminal);
    }
}

void ConnectionManager::connectTerminals(const Terminal* source, const Terminal* dest, const Wire* wire)
{
    m_connections.insert({ source, { dest, wire, false } });
    m_connections.insert({ dest, { source, wire, true } });
}

std::vector<ConnectionManager::Connection> ConnectionManager::getConnections(const Terminal* terminal) const
{
    std::vector<Connection> connections;
    for (auto itr = m_connections.find(terminal); itr != m_connections.end(); ++itr)
    {
        connections.push_back(itr->second);
    }
    return connections;
}

std::vector<ConnectionManager::Connection> ConnectionManager::getConnections(const ElectronicComponent* component) const
{
    std::vector<Connection> connections;
    for (auto& terminal : component->getTerminals())
    {
        STLTools::extend(connections, getConnections(terminal));
    }
    return connections;
}

std::vector<const Terminal*> ConnectionManager::getNeighbours(const Terminal* terminal) const
{
    std::vector<const Terminal*> neighbours;
    for (auto itr = m_connections.find(terminal); itr != m_connections.end(); ++itr)
    {
        neighbours.push_back(itr->second.terminal);
    }
    return neighbours;
}

bool ConnectionManager::hasPath(const Terminal* source, const Terminal* dest) const
{
    BreadthFirstSearch bfs(*this, source);
    return bfs.hasPathTo(dest);
}

void ConnectionManager::printConnections() const
{
    // Goes through each unique key in the multimap.
    for (auto itr = m_connections.begin(); itr != m_connections.end(); itr = m_connections.upper_bound(itr->first))
    {
        const auto& vertex = itr->first;

        QString connectionsStr;
        for (auto it = m_connections.find(vertex); it != m_connections.end(); ++it)
        {
            const auto& connection = it->second;
            connectionsStr.push_back(connection.terminal->objectName() + ", ");
        }

        qDebug() << vertex->objectName() << ":"
                 << "[" << connectionsStr << "]";
    }
}
