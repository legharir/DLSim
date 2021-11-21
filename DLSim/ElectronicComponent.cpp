#include "ElectronicComponent.h"

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

Terminal* ElectronicComponent::getIntersectingTerminal(const QPointF& scenePoint) const
{
    const auto it = std::find_if(
        m_terminals.begin(),
        m_terminals.end(),
        [&, this](const auto* terminal) { return terminal->containsScenePoint(scenePoint); });

    return it != m_terminals.end() ? *it : nullptr;
}

std::unordered_set<const Terminal*> ElectronicComponent::getTerminals() const
{
    return std::unordered_set<const Terminal*>{ m_terminals.begin(), m_terminals.end() };
}

void ElectronicComponent::addTerminal(Terminal* terminal)
{
    QObject::connect(terminal, &Terminal::mousePressed, this, &ElectronicComponent::beginWire);
    QObject::connect(terminal, &Terminal::mouseMoved, this, &ElectronicComponent::updateWire);
    QObject::connect(terminal, &Terminal::mouseReleased, this, &ElectronicComponent::endWire);

    m_terminals.insert(terminal);
}

QVariant ElectronicComponent::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == ItemPositionChange)
    {
        const auto delta = value.toPointF() - pos();
        emit moved(this, delta);
    }

    return QGraphicsItem::itemChange(change, value);
}

bool ElectronicComponent::containsScenePoint(const QPointF& scenePoint) const
{
    return contains(mapFromScene(scenePoint));
}
