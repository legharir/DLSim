#include "SimulationScene.h"

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

#include <QDebug>

#include "Battery.h"
#include "Led.h"
#include "Terminal.h"

SimulationScene::SimulationScene()
{
    addComponent(std::make_unique<Battery>());
    addComponent(std::make_unique<Led>());
}

void SimulationScene::addComponent(std::unique_ptr<ElectronicComponent> component)
{
    m_currentManager.addComponent(component.get());

    connect(component.get(), &ElectronicComponent::beginWire, this, &SimulationScene::onBeginWire);
    connect(component.get(), &ElectronicComponent::updateWire, this, &SimulationScene::onUpdateWire);
    connect(component.get(), &ElectronicComponent::endWire, this, &SimulationScene::onEndWire);

    connect(component.get(), &ElectronicComponent::moved, this, &SimulationScene::onElectronicComponentMoved);

    addItem(component.get());

    m_electronicComponents.push_back(std::move(component));
}

void SimulationScene::connectComponents(ElectronicComponent& source, ElectronicComponent& destination)
{
    source.addConnection({ true, *m_curWire, destination });
    destination.addConnection({ false, *m_curWire, source });
}

void SimulationScene::snapWireToTerminal(const Terminal& terminal)
{
    auto snappedLine = m_curWire->line();
    const auto terminalCenter = terminal.mapToScene(terminal.line().center());
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
    auto wireConnected = false;
    for (auto& component : m_electronicComponents)
    {
        // Check for and create connections between components.
        if (auto destinationTerminal = component->getIntersectingTerminal(point))
        {
            connectComponents(sourceComponent, *component);
            snapWireToTerminal(*destinationTerminal);
            m_wires.push_back(m_curWire);
            wireConnected = true;
        }

        // Unhighlight the terminal.
        component->setTerminalsHighlighted(false);
        component->update();
    }

    // Remove the wire if it didn't connect the component to another.
    if (!wireConnected)
    {
        removeItem(m_curWire);
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
