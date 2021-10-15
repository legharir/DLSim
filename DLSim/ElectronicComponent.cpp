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

const Terminal* ElectronicComponent::getIntersectingTerminal(const QPointF& scenePoint) const
{
    const auto it = std::find_if(
        m_terminals.begin(),
        m_terminals.end(),
        [&, this](const std::unique_ptr<Terminal>& terminal)
        {
            const auto point = terminal->mapFromScene(scenePoint);
            return terminal->contains(point);
        });

    return it != m_terminals.end() ? (*it).get() : nullptr;
}

void ElectronicComponent::addTerminal(std::unique_ptr<Terminal> terminal)
{
    QObject::connect(terminal.get(), &Terminal::mousePressed, this, &ElectronicComponent::beginWire);
    QObject::connect(terminal.get(), &Terminal::mouseMoved, this, &ElectronicComponent::updateWire);
    QObject::connect(
        terminal.get(), &Terminal::mouseReleased, [this](const QPointF& point) { emit endWire(point, *this); });

    m_terminals.push_back(std::move(terminal));
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

const std::vector<std::unique_ptr<Terminal>>& ElectronicComponent::getTerminals() const
{
    return m_terminals;
}
