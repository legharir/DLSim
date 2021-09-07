#include "SimulationScene.h"

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

#include <QDebug>

#include "Battery.h"
#include "Led.h"

SimulationScene::SimulationScene()
{
	Battery* battery = new Battery();
	addComponent(battery);

	Led* led = new Led();
	addComponent(led);
}

void SimulationScene::addComponent(ElectronicComponent* component)
{
	connect(component, &ElectronicComponent::beginWire, this, &SimulationScene::onBeginWire);
	connect(component, &ElectronicComponent::updateWire, this, &SimulationScene::onUpdateWire);
	connect(component, &ElectronicComponent::endWire, this, &SimulationScene::onEndWire);

	m_electronicComponents.push_back(component);
	addItem(component);
}

void SimulationScene::onBeginWire(QPointF point)
{
	m_drawingWire = true;
	m_curWire = new QGraphicsLineItem(QLineF(point, point));

	for (auto& component : m_electronicComponents)
	{
		component->setTerminalsHighlighted(true);
		component->update();
	}

	addItem(m_curWire);
}

void SimulationScene::onUpdateWire(QPointF point)
{
	auto line = m_curWire->line();
	line.setP2(point);
	m_curWire->setLine(line);
}

void SimulationScene::onEndWire(QPointF point)
{
	m_curWire = nullptr;

	for (auto& component : m_electronicComponents)
	{
		component->setTerminalsHighlighted(false);
	}
}
