#pragma once

#include <QGraphicsObject>

class Terminal;

class ElectronicComponent : public QGraphicsObject
{
	Q_OBJECT

public:
	ElectronicComponent();

	void setTerminalsHighlighted(bool highlight);

signals:
	void beginWire(QPointF point);
	void updateWire(QPointF point);
	void endWire(QPointF point);

protected:
	void addTerminal(Terminal* terminal);

	std::vector<Terminal*> m_terminals;
};

