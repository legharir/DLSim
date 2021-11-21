#include "SimulationScene.h"

#include <queue>

#include <QGraphicsSceneMouseEvent>

#include "STLTools.h"

#include "Battery.h"
#include "Led.h"
#include "Switch.h"
#include "Terminal.h"
#include "Wire.h"

SimulationScene::SimulationScene()
{
    addComponent(new Battery());
    addComponent(new Led());
    addComponent(new Switch());
}

void SimulationScene::addComponent(ElectronicComponent* component)
{
    connect(component, &ElectronicComponent::beginWire, this, &SimulationScene::onBeginWire);
    connect(component, &ElectronicComponent::updateWire, this, &SimulationScene::onUpdateWire);
    connect(component, &ElectronicComponent::endWire, this, &SimulationScene::onEndWire);
    connect(component, &ElectronicComponent::moved, this, &SimulationScene::onElectronicComponentMoved);

    QGraphicsScene::addItem(component);

    m_electronicComponents.insert(std::move(component));
}

ElectronicComponent* SimulationScene::getComponent(const ElectronicComponent* component)
{
    auto itr = m_electronicComponents.find(const_cast<ElectronicComponent*>(component));
    assert(itr != m_electronicComponents.end());
    return itr != m_electronicComponents.end() ? *itr : nullptr;
}

Wire* SimulationScene::getWire(const Wire* wire)
{
    auto itr = m_wires.find(const_cast<Wire*>(wire));
    assert(itr != m_wires.end());
    return itr != m_wires.end() ? *itr : nullptr;
}

void SimulationScene::snapWireToTerminal(const Terminal& terminal)
{
    auto snappedLine = m_curWire->line();
    snappedLine.setP2(terminal.center());
    m_curWire->setLine(snappedLine);
}

void SimulationScene::onBeginWire(const Terminal* terminal, const QPointF& point)
{
    m_curWire = new Wire(QLineF(point, point));

    for (auto& component : m_electronicComponents)
    {
        if (component == terminal->getComponent())
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

    bool connected = false;
    for (const auto& component : m_electronicComponents)
    {
        if (auto destTerminal = component->getIntersectingTerminal(point))
        {
            createConnections(sourceTerminal, destTerminal);
            snapWireToTerminal(*destTerminal);
            connected = true;
        }
    }

    if (!connected)
    {
        removeItem(m_curWire);
        delete m_curWire;
        m_curWire = nullptr;
    }
    else
    {
        m_wires.insert(m_curWire);
    }

    m_connectionManager.printConnections();
    //highlightConductingPaths();
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

        auto* wire = getWire(connection.wire);
        wire->setLine(line);
    }
}

void SimulationScene::highlightConductingPaths()
{
    for (const auto& component : m_electronicComponents)
    {
        if (const auto battery = dynamic_cast<Battery*>(component))
        {
            if (m_connectionManager.hasPath(battery->getNegativeTerminal(), battery->getPositiveTerminal()))
            {
                std::queue<const Terminal*> terminals;
                terminals.push(battery->getNegativeTerminal());

                while (!terminals.empty())
                {
                    auto& terminal = terminals.front();

                    auto* component = getComponent(terminal->getComponent());
                    component->setTerminalsHighlighted(true);

                    for (const auto& connection : m_connectionManager.getConnections(terminal))
                    {
                        auto* wire = getWire(connection.wire);
                        wire->setHighlighted(true);
                        terminals.push(connection.terminal);
                    }

                    terminals.pop();
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
    m_connectionManager.connectTerminals(sourceTerminal, destTerminal, m_curWire);
}
