#include "ElectronicComponent.h"

#include "Terminal.h"

ElectronicComponent::ElectronicComponent()
{
    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}

void ElectronicComponent::setTerminalsHighlighted(bool highlight)
{
    for (auto& terminal : m_terminals)
    {
        terminal->setHighlighted(highlight);
    }
}

std::optional<const Terminal*> ElectronicComponent::getTerminal(const QPointF& scenePoint)
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
    QObject::connect(terminal, &Terminal::mouseReleased, this, &ElectronicComponent::endWire);
}
