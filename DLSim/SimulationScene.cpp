#include "SimulationScene.h"

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

#include <QDebug>

#include "Battery.h"
#include "Led.h"
#include "Terminal.h"

SimulationScene::SimulationScene()
{
    Battery* battery = new Battery();
    addComponent(battery);

    Led* led = new Led();
    addComponent(led);
}

void SimulationScene::addComponent(ElectronicComponent* component)
{
    connect(component, &ElectronicComponent::beginWire, this, &SimulationScene::onBeginWire);
    connect(component, &ElectronicComponent::updateWire, this, &SimulationScene::onUpdateWire);
    connect(component, &ElectronicComponent::endWire, this, &SimulationScene::onEndWire);

    connect(component, &ElectronicComponent::moved, this, &SimulationScene::onElectronicComponentMoved);

    m_electronicComponents.push_back(component);
    addItem(component);
}

void SimulationScene::snapWireToTerminal(const Terminal* terminal)
{
    auto snappedLine = m_curWire->line();
    const auto terminalCenter = terminal->mapToScene(terminal->line().center());
    snappedLine.setP2(terminalCenter);
    m_curWire->setLine(snappedLine);
}

void SimulationScene::onBeginWire(const QPointF& point)
{
    m_curWire = new QGraphicsLineItem(QLineF(point, point));

    for (auto& component : m_electronicComponents)
    {
        component->setTerminalsHighlighted(true);
        component->update();
    }

    addItem(m_curWire);
}

void SimulationScene::onUpdateWire(const QPointF& point)
{
    auto line = m_curWire->line();
    line.setP2(point);
    m_curWire->setLine(line);
}

void SimulationScene::onEndWire(const QPointF& point, ElectronicComponent& sourceComponent)
{
    for (auto& component : m_electronicComponents)
    {
        // Check for and create connections between components.
        if (auto destinationTerminal = component->getTerminal(point))
        {
            component->addConnection({ false, *m_curWire, sourceComponent });
            sourceComponent.addConnection({ true, *m_curWire, *component });
            snapWireToTerminal(*destinationTerminal);
            m_wires.push_back(std::move(m_curWire));
        }

        component->setTerminalsHighlighted(false);
        component->update();
    }

    m_curWire = nullptr;
}

void SimulationScene::onElectronicComponentMoved(ElectronicComponent& component, const QPointF& delta)
{
    for (auto& connection : component.m_connections)
    {
        auto line = connection.wire.line();
        if (connection.isSource)
        {
            line.setP1(line.p1() + delta);
        }
        else
        {
            line.setP2(line.p2() + delta);
        }
        connection.wire.setLine(line);
    }
}
