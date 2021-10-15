#pragma once

#include <memory>

#include <QGraphicsScene>

#include "CurrentManager.h"

class ElectronicComponent;
class Terminal;

class SimulationScene : public QGraphicsScene
{
    Q_OBJECT;

public:
    SimulationScene();

private:
    std::vector<std::unique_ptr<ElectronicComponent>> m_electronicComponents;
    std::vector<QGraphicsLineItem*> m_wires;

    QGraphicsLineItem* m_curWire = nullptr;

    void addComponent(std::unique_ptr<ElectronicComponent> component);

    void connectComponents(ElectronicComponent& source, ElectronicComponent& destination);
    void snapWireToTerminal(const Terminal& terminal);

    void onBeginWire(const QPointF& point);
    void onUpdateWire(const QPointF& point);
    void onEndWire(const QPointF& point, ElectronicComponent& component);

    void onElectronicComponentMoved(ElectronicComponent& component, const QPointF& delta);

    CurrentManager m_currentManager;
};
