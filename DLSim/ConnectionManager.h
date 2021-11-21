#pragma once

#include <map>
#include <unordered_set>
#include <vector>

class ElectronicComponent;
class Terminal;
class Wire;

class ConnectionManager
{
public:
    struct Connection
    {
        const Terminal* terminal;
        const Wire* wire;
        bool isSource;
    };

    void removeComponent(const ElectronicComponent* component);

    void connectTerminals(const Terminal* source, const Terminal* dest, const Wire* wire);

    // Returns all the connections from/to the given terminal.
    std::vector<Connection> getConnections(const Terminal* terminal) const;
    // Returns all the connections from/to every terminal of the given component.
    std::vector<Connection> getConnections(const ElectronicComponent* component) const;

    // Returns the terminals that are connected to the given terminal.
    std::vector<const Terminal*> getNeighbours(const Terminal* terminal) const;

    bool hasPath(const Terminal* source, const Terminal* dest) const;

    void printConnections() const;

private:
    std::multimap<const Terminal*, Connection> m_connections;
};
