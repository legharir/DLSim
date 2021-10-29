#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include <QGraphicsScene>

#include "ConnectionManager.h"
#include "CurrentManager.h"

class ElectronicComponent;
class Terminal;
class Wire;

class SimulationScene : public QGraphicsScene
{
    Q_OBJECT;

public:
    SimulationScene();

private:
    std::vector<std::unique_ptr<ElectronicComponent>> m_electronicComponents;

    Wire* m_curWire = nullptr;

    void addComponent(std::unique_ptr<ElectronicComponent> electronicComponent);

    void onComponentsChanged();

    void snapWireToTerminal(const Terminal& terminal);

    void onBeginWire(const Terminal* terminal, const QPointF& point);
    void onUpdateWire(const QPointF& point);
    void onEndWire(Terminal* terminal, const QPointF& point);

    void onElectronicComponentMoved(const ElectronicComponent* component, const QPointF& delta);

    void highlightConductingPaths();

    void setTerminalsHighlighted(bool highlighted);

    void createConnections(Terminal* sourceTerminal, Terminal* destTerminal);

    CurrentManager m_currentManager;
    ConnectionManager m_connectionManager;
};
