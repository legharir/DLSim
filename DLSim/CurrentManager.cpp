#include "CurrentManager.h"

#include "Battery.h"
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
}

bool CurrentManager::canCurrentFlow() const
{
    return false;
}
