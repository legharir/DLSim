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

void ElectronicComponent::addTerminal(Terminal* terminal)
{
	m_terminals.push_back(terminal);
	QObject::connect(terminal, &Terminal::mousePressed, this, &ElectronicComponent::beginWire);
	QObject::connect(terminal, &Terminal::mouseMoved, this, &ElectronicComponent::updateWire);
	QObject::connect(terminal, &Terminal::mouseReleased, this, &ElectronicComponent::endWire);
}
