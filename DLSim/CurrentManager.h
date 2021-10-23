#pragma once

#include <utility>

#include "Graph.h"

class ElectronicComponent;
class Terminal;

class CurrentManager
{
public:
    void addComponent(const ElectronicComponent* component);
    void removeComponent(const ElectronicComponent* component);

    void connectTerminals(const Terminal* source, const Terminal* dest);

    bool hasPath(const Terminal* source, const Terminal* dest) const;

    void printGraph() const;

private:
    Graph<const Terminal*> m_circuitGraph;
};
