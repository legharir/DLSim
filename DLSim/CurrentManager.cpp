#include "CurrentManager.h"

#include "Battery.h"
#include "BreadthFirstSearch.h"
#include "ElectronicComponent.h"
#include "Terminal.h"

void CurrentManager::addComponent(const ElectronicComponent* component)
{
    for (const auto& terminal : component->getTerminals())
    {
        m_circuitGraph.addVertex({ terminal.get() });
    }
}

void CurrentManager::removeComponent(const ElectronicComponent* component)
{
    for (const auto& terminal : component->getTerminals())
    {
        m_circuitGraph.removeVertex({ terminal.get() });
    }
}

void CurrentManager::connectTerminals(const Terminal* source, const Terminal* dest)
{
    m_circuitGraph.addEdge(source, dest);
    m_circuitGraph.addEdge(dest, source);
}

bool CurrentManager::hasPath(const Terminal* source, const Terminal* dest) const
{
    BreadthFirstSearch bfs(m_circuitGraph, source);
    return bfs.hasPathTo(dest);
}

void CurrentManager::printGraph() const
{
    m_circuitGraph.print();
}
