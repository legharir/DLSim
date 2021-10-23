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

void SimulationScene::connectTerminals(Terminal* source, Terminal* dest)
{
    m_currentManager.connectTerminals(source, dest);
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
    m_curWire = new QGraphicsLineItem(QLineF(point, point));

    for (auto& component : m_electronicComponents)
    {
        //if (component.get() == terminal->getComponent())
        //{
        //    continue;
        //}

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

void SimulationScene::onEndWire(const Terminal* sourceTerminal, const QPointF& point)
{
    auto wireConnected = false;
    for (auto& component : m_electronicComponents)
    {
        // Check for and create connections between components.
        if (auto destinationTerminal = component->getIntersectingTerminal(point))
        {
            //connectTerminals(sourceTerminal, destinationTerminal);
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

    m_currentManager.printGraph();
}

void SimulationScene::onElectronicComponentMoved(ElectronicComponent& component, const QPointF& delta)
{
    //for (auto& connection : component.)
    //{
    //    auto line = connection.wire.line();
    //    if (connection.isSource)
    //    {
    //        line.setP1(line.p1() + delta);
    //    }
    //    else
    //    {
    //        line.setP2(line.p2() + delta);
    //    }
    //    connection.wire.setLine(line);
    //}
}
