#pragma once

#include <unordered_map>
#include <vector>

class QGraphicsLineItem;
class ElectronicComponent;
class Wire;

class ConnectionManager
{
public:
    struct Connection
    {
        Wire* wire;
        bool isSource;
    };

    using ConnectionMap = std::unordered_map<const ElectronicComponent*, std::vector<Connection>>;

    void
    createConnection(const ElectronicComponent* sourceComponent, const ElectronicComponent* destComponent, Wire* wire);
    const std::vector<Connection>& getConnections(const ElectronicComponent* component);

private:
    ConnectionMap m_connections;
};
