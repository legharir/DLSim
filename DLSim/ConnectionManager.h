#pragma once

#include <unordered_map>
#include <vector>

class QGraphicsLineItem;
class ElectronicComponent;

class ConnectionManager
{
public:
    struct Connection
    {
        QGraphicsLineItem* wire;
        bool isSource;
    };

    using ConnectionMap = std::unordered_map<const ElectronicComponent*, std::vector<Connection>>;

    void createConnection(
        const ElectronicComponent* sourceComponent, const ElectronicComponent* destComponent, QGraphicsLineItem* wire);
    const std::vector<Connection>& getConnections(const ElectronicComponent* component);

private:
    ConnectionMap m_connections;
};
