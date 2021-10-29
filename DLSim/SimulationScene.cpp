#include "SimulationScene.h"

#include <QGraphicsSceneMouseEvent>

#include <QDebug>

#include "Battery.h"
#include "Led.h"
#include "Terminal.h"
#include "Wire.h"

SimulationScene::SimulationScene()
{
    addComponent(std::make_unique<Battery>());
    addComponent(std::make_unique<Led>());
}

void SimulationScene::addComponent(std::unique_ptr<ElectronicComponent> electronicComponent)
{
    m_electronicComponents.push_back(std::move(electronicComponent));
    ElectronicComponent* component = m_electronicComponents.back().get();

    connect(component, &ElectronicComponent::beginWire, this, &SimulationScene::onBeginWire);
    connect(component, &ElectronicComponent::updateWire, this, &SimulationScene::onUpdateWire);
    connect(component, &ElectronicComponent::endWire, this, &SimulationScene::onEndWire);

    connect(component, &ElectronicComponent::moved, this, &SimulationScene::onElectronicComponentMoved);

    QGraphicsScene::addItem(component);

    m_currentManager.addComponent(component);

    onComponentsChanged();
}

void SimulationScene::onComponentsChanged()
{
    for (const auto& component : m_electronicComponents)
    {
        if (const auto battery = dynamic_cast<Battery*>(component.get()))
        {
            const auto* negativeTerminal = battery->getNegativeTerminal();
            const auto* positiveTerminal = battery->getPositiveTerminal();
            if (m_currentManager.hasPath(negativeTerminal, positiveTerminal))
            {
            }
        }
    }
}

void SimulationScene::snapWireToTerminal(const Terminal& terminal)
{
    auto snappedLine = m_curWire->line();
    const auto terminalCenter = terminal.mapToScene(terminal.line().center());
    snappedLine.setP2(terminalCenter);
    m_curWire->setLine(snappedLine);
}

void SimulationScene::onBeginWire(const Terminal* terminal, const QPointF& point)
{
    m_curWire = new Wire(QLineF(point, point));

    for (auto& component : m_electronicComponents)
    {
        if (component.get() == terminal->getComponent())
        {
            continue;
        }

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

void SimulationScene::onEndWire(Terminal* sourceTerminal, const QPointF& point)
{
    setTerminalsHighlighted(false);

    //auto destTerminal = std::find_if(
    //    m_electronicComponents.begin(),
    //    m_electronicComponents.end(),
    //    [&](auto& component) { return component->getIntersectingTerminal(point); });


    auto wireConnected = false;

    for (auto& component : m_electronicComponents)
    {
        // If the wire was placed on a terminal, create a connection to it.
        if (auto destTerminal = component->getIntersectingTerminal(point))
        {
            createConnections(sourceTerminal, destTerminal);
            snapWireToTerminal(*destTerminal);
            wireConnected = true;
            break;
        }
    }

    // Remove the wire if it didn't connect the component to another.
    if (!wireConnected)
    {
        removeItem(m_curWire);
    }

    m_curWire = nullptr;

    m_currentManager.printGraph();
    highlightConductingPaths();
}

void SimulationScene::onElectronicComponentMoved(const ElectronicComponent* component, const QPointF& delta)
{
    for (auto& connection : m_connectionManager.getConnections(component))
    {
        auto line = connection.wire->line();
        if (connection.isSource)
        {
            line.setP1(line.p1() + delta);
        }
        else
        {
            line.setP2(line.p2() + delta);
        }
        connection.wire->setLine(line);
    }
}

void SimulationScene::highlightConductingPaths()
{
    for (const auto& component : m_electronicComponents)
    {
        if (const auto battery = dynamic_cast<Battery*>(component.get()))
        {
            if (m_currentManager.hasPath(battery->getNegativeTerminal(), battery->getPositiveTerminal()))
            {
                for (const auto& connection : m_connectionManager.getConnections(battery))
                {
                    connection.wire->setHighlighted(true);
                    connection.wire->update();
                }
            }
        }
    }
}

void SimulationScene::setTerminalsHighlighted(bool highlighted)
{
    for (auto& component : m_electronicComponents)
    {
        component->setTerminalsHighlighted(false);
        component->update();
    }
}

void SimulationScene::createConnections(Terminal* sourceTerminal, Terminal* destTerminal)
{
    auto* sourceComponent = sourceTerminal->getComponent();
    auto* destComponent = destTerminal->getComponent();

    m_connectionManager.createConnection(sourceComponent, destComponent, m_curWire);
    m_currentManager.connectTerminals(sourceTerminal, destTerminal);
}
