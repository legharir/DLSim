#include "ConnectionManager.h"

void ConnectionManager::createConnection(
    const ElectronicComponent* sourceComponent, const ElectronicComponent* destComponent, QGraphicsLineItem* wire)
{
    m_connections[sourceComponent].push_back({ wire, true });
    m_connections[destComponent].push_back({ wire, false });
}

const std::vector<ConnectionManager::Connection>&
ConnectionManager::getConnections(const ElectronicComponent* component)
{
    return m_connections[component];
}
