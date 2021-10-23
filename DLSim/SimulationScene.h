#pragma once

#include <memory>
#include <unordered_map>

#include <QGraphicsScene>

#include "CurrentManager.h"

class ElectronicComponent;
class Terminal;

class SimulationScene : public QGraphicsScene
{
    Q_OBJECT;

public:
    struct Connection
    {
        const ElectronicComponent& component;
        QGraphicsLineItem& wire;
    };

    SimulationScene();

private:
    std::vector<std::unique_ptr<ElectronicComponent>> m_electronicComponents;
    std::vector<QGraphicsLineItem*> m_wires;

    QGraphicsLineItem* m_curWire = nullptr;

    void addComponent(std::unique_ptr<ElectronicComponent> electronicComponent);

    void onComponentsChanged();

    void connectTerminals(Terminal* source, Terminal* dest);
    void snapWireToTerminal(const Terminal& terminal);

    void onBeginWire(const Terminal* terminal, const QPointF& point);
    void onUpdateWire(const QPointF& point);
    void onEndWire(const Terminal* terminal, const QPointF& point);

    void onElectronicComponentMoved(ElectronicComponent& component, const QPointF& delta);

    CurrentManager m_currentManager;

    std::unordered_map<const ElectronicComponent*, Connection> m_connections;
};
