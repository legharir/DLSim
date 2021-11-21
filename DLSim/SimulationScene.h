#pragma once

#include <unordered_set>

#include <QGraphicsScene>

#include "ConnectionManager.h"

class ElectronicComponent;
class Terminal;
class Wire;

class SimulationScene : public QGraphicsScene
{
    Q_OBJECT;

public:
    SimulationScene();

private:
    void addComponent(ElectronicComponent* component);

    // TODO: can probably use a template func to do this kind of thing.
    ElectronicComponent* getComponent(const ElectronicComponent* component);
    Wire* getWire(const Wire* wire);

    void createConnections(Terminal* sourceTerminal, Terminal* destTerminal);
    void highlightConductingPaths();
    void snapWireToTerminal(const Terminal& terminal);
    void setTerminalsHighlighted(bool highlighted);

    void onBeginWire(const Terminal* terminal, const QPointF& point);
    void onUpdateWire(const QPointF& point);
    void onEndWire(Terminal* terminal, const QPointF& point);
    void onElectronicComponentMoved(const ElectronicComponent* component, const QPointF& delta);

    std::unordered_set<ElectronicComponent*> m_electronicComponents;
    std::unordered_set<Wire*> m_wires;
    Wire* m_curWire = nullptr;

    ConnectionManager m_connectionManager;
};
