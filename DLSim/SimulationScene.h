#pragma once

#include <QGraphicsScene>

class ElectronicComponent;
class Terminal;

class SimulationScene : public QGraphicsScene
{
    Q_OBJECT

public:
    SimulationScene();

private:
    std::vector<ElectronicComponent*> m_electronicComponents;
    std::vector<QGraphicsLineItem*> m_wires;

    QGraphicsLineItem* m_curWire = nullptr;

    void addComponent(ElectronicComponent* component);

    void snapWireToTerminal(const Terminal* terminal);

    void onBeginWire(const QPointF& point);
    void onUpdateWire(const QPointF& point);
    void onEndWire(const QPointF& point, ElectronicComponent& component);

    void onElectronicComponentMoved(ElectronicComponent& component, const QPointF& delta);
};
