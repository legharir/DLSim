#include "ElectronicComponent.h"

#include <QDebug>

#include "Terminal.h"

ElectronicComponent::ElectronicComponent()
{
    setFlags(ItemIsSelectable | ItemIsMovable | ItemIsFocusable | ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
}

void ElectronicComponent::setTerminalsHighlighted(bool highlight)
{
    for (auto& terminal : m_terminals)
    {
        terminal->setHighlighted(highlight);
    }
}

std::optional<Terminal*> ElectronicComponent::getTerminal(const QPointF& scenePoint)
{
    const auto it = std::find_if(m_terminals.begin(), m_terminals.end(), [&, this](const Terminal* terminal) {
        const auto point = terminal->mapFromScene(scenePoint);
        return terminal->contains(point);
    });

    if (it != m_terminals.end())
    {
        return { *it };
    }
    return {};
}

void ElectronicComponent::addTerminal(Terminal* terminal)
{
    m_terminals.push_back(terminal);
    QObject::connect(terminal, &Terminal::mousePressed, this, &ElectronicComponent::beginWire);
    QObject::connect(terminal, &Terminal::mouseMoved, this, &ElectronicComponent::updateWire);
    QObject::connect(terminal, &Terminal::mouseReleased, [this](const QPointF& point) { emit endWire(point, *this); });
}

void ElectronicComponent::addConnection(const Connection& connection)
{
    m_connections.push_back(connection);
}

QVariant ElectronicComponent::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == ItemPositionChange)
    {
        const auto delta = value.toPointF() - pos();
        emit moved(*this, delta);
    }

    return QGraphicsItem::itemChange(change, value);
}
